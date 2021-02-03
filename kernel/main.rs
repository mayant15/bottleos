#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(bottleos::test_runner)]
#![reexport_test_harness_main = "test_main"]

use core::panic::PanicInfo;
use bottleos::kprintln;

#[no_mangle]
pub extern "C" fn _start() -> ! {
    kprintln!("Hello kernel world!");

    bottleos::init();

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
