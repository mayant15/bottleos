#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(bottleos::test_runner)]
#![reexport_test_harness_main = "test_main"]

use bootloader::{entry_point, BootInfo};
use bottleos::kprintln;
use core::panic::PanicInfo;

entry_point!(kernel_main);

fn kernel_main(boot_info: &'static BootInfo) -> ! {
    use bottleos::memory;
    use bottleos::memory::BootInfoFrameAllocator;
    use x86_64::{structures::paging::Page, VirtAddr};

    kprintln!("Hello kernel world!");
    bottleos::init();

    let phys_mem_offset = VirtAddr::new(boot_info.physical_memory_offset);
    let mut mapper = unsafe { memory::init(phys_mem_offset) };

    let mut frame_allocator = unsafe { BootInfoFrameAllocator::init(&boot_info.memory_map) };

    // map an unused page
    let page = Page::containing_address(VirtAddr::new(0));
    memory::create_example_mapping(page, &mut mapper, &mut frame_allocator);

    let page_ptr: *mut u64 = page.start_address().as_mut_ptr();
    unsafe { page_ptr.offset(400).write_volatile(0x_f021_f077_f065_f04e) };

    #[cfg(test)]
    test_main();

    kprintln!("Kernel did not crash. Phew.");
    bottleos::hlt_loop();
}

#[cfg(not(test))]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    kprintln!("{}", info);
    bottleos::hlt_loop();
}

#[cfg(test)]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    bottleos::test_panic_handler(info)
}
