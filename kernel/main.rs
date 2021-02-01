#![no_std]
#![no_main]

use core::panic::PanicInfo;

#[no_mangle]
pub extern "C" fn _start() -> ! {
    kprintln!("Hello kernel world!");
    panic!("Testing a panic in main");
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    kprintln!("{}", info);
    loop {}
}

mod vga_buffer;
