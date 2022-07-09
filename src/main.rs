#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(bottleos::test_runner)]
#![reexport_test_harness_main = "test_main"]

// extern crate alloc;

//use bootloader::{entry_point, BootInfo};
use bottleos::stivale2;
use bottleos::{kprint, kprintln};
use core::panic::PanicInfo;

// entry_point!(kernel_main);

#[no_mangle]
pub extern "C" fn _start(info_ptr: u64) -> ! {
    stivale2::init(info_ptr);

    kprint!(">> Initializing kernel...");
    bottleos::init();
    kprint!(" [ok!]");

    loop {}
}

#[allow(dead_code)]
fn kernel_main(_boot_info: &'static str) -> ! {
    // use bottleos::memory::{self, allocator, BootInfoFrameAllocator};
    // use bottleos::proc;
    // use x86_64::VirtAddr;

    kprint!(">> Initializing kernel...");
    bottleos::init();
    kprintln!(" [ok!]");

    /*
    kprint!(">> Initializing heap memory...");
    let phys_mem_offset = VirtAddr::new(boot_info.physical_memory_offset);
    let mut mapper = unsafe { memory::init(phys_mem_offset) };
    let mut frame_allocator = unsafe { BootInfoFrameAllocator::init(&boot_info.memory_map) };
    allocator::init_heap(&mut mapper, &mut frame_allocator).expect("heap initialization failed");
    kprintln!(" [ok!]");
    */

    #[cfg(test)]
    test_main();

    // proc::start();
    loop {}
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
