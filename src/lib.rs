pub mod algorithm;
pub mod world;

use nalgebra::Vector3;


pub struct Particle<T> {
    pub property: T,
}

pub struct World<TFloat> {
    positions: Vec<Vector3<TFloat>>,
}

impl<TFloat> World<TFloat> {
    pub fn get_position(&self) -> &Vector3<TFloat> {
        &self.positions[0]
    }
}
