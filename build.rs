fn main() {
    println!("cargo:rustc-link-arg=-Tboot/linker.ld");
    println!("cargo:rustc-link-arg=-Lboot");
    println!("cargo:rustc-link-lib=static=boot");

    cc::Build::new()
        .file("boot/boot.c")
        .compile("boot")
}

