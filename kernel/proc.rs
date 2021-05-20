use crate::kprintln;
use x86_64::instructions::hlt;
use alloc::{boxed::Box, rc::Rc, vec, vec::Vec};

/// All processes in the system should be in this queue
struct JobQueue {
    // TODO
}

/// All processes that are ready to be executed should be in this queue
struct ReadyQueue {
    // TODO
}

pub enum ProcessState {
    Start,
    Running,
    Waiting,
    Ready,
    End,
}

pub struct Process {
    pid: u32,
    state: ProcessState,
}

pub struct Scheduler {
    // TODO
}

impl Scheduler {
    pub fn new() -> Self {
        Scheduler {}
    }

    pub fn start(&self) -> ! {
        // TODO: IPC. Should these closures be allowed to capture their surroundings? Should they run
        // immediately? Should I have a init -> set_data -> start -> join API?
        let proc1 = Process::new(|| {
            let heap_value = Box::new(41);
            kprintln!("heap_value at {:p}", heap_value);

            let mut vec = Vec::new();
            for i in 0..500 {
                vec.push(i);
            }
            kprintln!("vec at {:p}", vec.as_slice());
        });

        let proc2 = Process::new(|| {
            let reference_counted = Rc::new(vec![1, 2, 3]);
            let cloned_reference = reference_counted.clone();
            kprintln!(
                "current reference count is {}",
                Rc::strong_count(&cloned_reference)
            );
            core::mem::drop(reference_counted);
            kprintln!(
                "reference count is {} now",
                Rc::strong_count(&cloned_reference)
            );
        });

        // Scheduler main loop
        loop {
            self.step();
        }
    }

    fn step(&self) {
        hlt();
    }
}

impl Default for Scheduler {
    fn default() -> Self {
        Scheduler::new()
    }
}

impl Process {
    pub fn new(task: impl Fn()) -> Self {
        // Add task to queue
        Process {
            pid: 0,
            state: ProcessState::Ready,
        }
    }
}

