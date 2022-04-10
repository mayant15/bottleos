extern "C" {
    fn stivale2_init(ptr: u64) -> i8;
    fn stivale2_term_write(s: *const u8, len: usize);
}

pub fn init(ptr: u64) -> i8 {
    unsafe { stivale2_init(ptr) }
}

pub fn write<'a>(s: &'a str) {
    unsafe {
        stivale2_term_write(s.as_ptr(), s.chars().count());
    }
}

pub fn writeln<'a>(s: &'a str) {
    write(s);
    write("\n");
}
