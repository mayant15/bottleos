#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(bottleos::test_runner)]
#![reexport_test_harness_main = "test_main"]

extern crate alloc;

use bootloader::{entry_point, BootInfo};
use bottleos::kprintln;
use core::panic::PanicInfo;

entry_point!(kernel_main);

fn kernel_main(boot_info: &'static BootInfo) -> ! {
    use bottleos::allocator;
    use bottleos::memory::{self, BootInfoFrameAllocator};
    use bottleos::proc;
    use x86_64::VirtAddr;

    kprintln!(">> Initializing kernel...");
    bottleos::init();
    kprintln!(">>    [ok!]");

    kprintln!(">> Initializing heap memory...");
    let phys_mem_offset = VirtAddr::new(boot_info.physical_memory_offset);
    let mut mapper = unsafe { memory::init(phys_mem_offset) };
    let mut frame_allocator = unsafe { BootInfoFrameAllocator::init(&boot_info.memory_map) };
    allocator::init_heap(&mut mapper, &mut frame_allocator).expect("heap initialization failed");
    kprintln!(">>    [ok!]");

    #[cfg(test)]
    test_main();
    
    kprintln!(">> Starting kernel processes...");
    proc::start();
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
