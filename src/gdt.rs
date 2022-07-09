use lazy_static::lazy_static;
use x86_64::registers::segmentation::{CS, DS, Segment};
use x86_64::structures::gdt::{Descriptor, GlobalDescriptorTable, SegmentSelector};
use x86_64::structures::tss::TaskStateSegment;
use x86_64::VirtAddr;

pub const DOUBLE_FAULT_IST_INDEX: u16 = 0;

lazy_static! {
    static ref TSS: TaskStateSegment = {
        let mut tss = TaskStateSegment::new();
        tss.interrupt_stack_table[DOUBLE_FAULT_IST_INDEX as usize] = {
            const STACK_SIZE: usize = 4096 * 5;
            static mut STACK: [u8; STACK_SIZE] = [0; STACK_SIZE];

            let stack_start = VirtAddr::from_ptr(unsafe { &STACK });
            stack_start + STACK_SIZE
        };
        tss
    };
}

struct Selectors {
    code: SegmentSelector,
    data: SegmentSelector,
    tss: SegmentSelector,
}

lazy_static! {
    /// Global GDT instance. This is required because the structure must have a static lifetime
    static ref GDT: (GlobalDescriptorTable, Selectors) = {
        let mut gdt = GlobalDescriptorTable::new();

    // NOTE: I do not need to add a null descriptor myself
    // https://docs.rs/x86_64/latest/x86_64/structures/gdt/struct.GlobalDescriptorTable.html
        let code = gdt.add_entry(Descriptor::kernel_code_segment());
        let data = gdt.add_entry(Descriptor::kernel_data_segment());
        let tss = gdt.add_entry(Descriptor::tss_segment(&TSS));

        // Return the tuple
        (
            gdt,
            Selectors {
                code,
                data,
                tss,
            },
        )
    };
}


/// Minimal GDT configuration with a TSS
pub fn init() {
    // Load the GDT
    GDT.0.load();
    unsafe {
        // Set GDT selectors to appropriate registers
        CS::set_reg(GDT.1.code);
        DS::set_reg(GDT.1.data);
        // load_tss(GDT.1.tss_selector);
    }
}
