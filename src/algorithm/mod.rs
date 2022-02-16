mod simple_sph;
pub use simple_sph::SimpleSmoothedParticleHydrodymamics;

pub trait IAlgorithm {
    fn execute(&mut self);
}
