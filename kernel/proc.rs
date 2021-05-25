use crate::kprintln;
use x86_64::instructions::hlt;
use alloc::{boxed::Box, rc::Rc, vec, vec::Vec, collections::VecDeque, string::String};
use lazy_static::lazy_static;
use spin::Mutex;

type ProcessQueue = alloc::collections::VecDeque<ProcessBlock>;

lazy_static! {
    /// A singleton instance of the Scheduler class to control processes
    static ref SCHEDULER: Mutex<Scheduler> = Mutex::new(Scheduler { 
        jobs: ProcessQueue::new(),
        ready_jobs: ProcessQueue::new(),
        next_pid: 0,
    });
}

pub fn start() -> ! {
    create_kernel_processes();
    SCHEDULER.lock().start();
}

#[derive(Debug, PartialEq, Eq)]
pub enum ProcessState {
    Start,
    Running,
    Waiting,
    Ready,
    End,
}

#[derive(Debug)]
struct ProcessBlock {
    pid: usize,
    state: ProcessState,
}

/// An interface to manipulate processes. The ProcessBlock is the actual internal representation.
#[derive(Debug)]
pub struct Process {
    pid: usize,
}

impl Process {
    // TODO: This should be atomic, don't pre-empt a thread that's creating a child process.
    pub fn new(task: impl Fn()) -> Self {
        // Create a process block
        let pid = SCHEDULER.lock().get_next_pid();
        let block = ProcessBlock {
            pid: pid,
            state: ProcessState::Start,
        };

        // NOTE: Disable interrupts here?
        SCHEDULER.lock().register_process(block);

        // Return an interface to this process block
        Process {
            pid: pid,
        }
    }

    pub fn is_valid(&self) -> bool {
        true
    }

    pub fn join(&self) -> Result<(), String> {
        Ok(())
    }
}

fn create_kernel_processes() {
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
}

#[derive(Debug)]
struct Scheduler {
    // TODO: No Mutexes here, everything is running on a single core. Make this thread-safe
    jobs: ProcessQueue,
    ready_jobs: ProcessQueue,

    next_pid: usize,
}

impl Scheduler {
    fn start(&self) -> ! {
        self.dump();
        loop {
            self.step();
        }
    }

    fn dump(&self) {
        kprintln!("SCHEDULER DUMP:");
        kprintln!("{:?}", self);
    }

    fn step(&self) {
        hlt();
    }

    fn get_next_pid(&self) -> usize {
        self.next_pid
    }

    fn register_process(&mut self, block: ProcessBlock) { 
        self.jobs.push_back(block);
        self.next_pid += 1;
    }
}


#[test_case]
fn test_scheduler_get_next_pid() {
    let mut guard = SCHEDULER.lock();
    assert_eq!(0, guard.get_next_pid());
    guard.next_pid += 1;
    assert_eq!(1, guard.get_next_pid());
}


#[test_case]
fn test_scheduler_register_process() {
    let mut guard = SCHEDULER.lock();
    let block = ProcessBlock {
        pid: 0,
        state: ProcessState::Start,
    };
    guard.jobs.push_back(block);

    assert_eq!(1, guard.jobs.len());

    let back = guard.jobs.back();
    assert!(back.is_some());
    assert_eq!(0, back.unwrap().pid);
    assert_eq!(ProcessState::Start, back.unwrap().state);
}

