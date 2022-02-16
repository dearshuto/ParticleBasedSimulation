mod rapier_world;

pub use rapier_world::RapierWorld;

pub trait IWorld {
    fn execute<T>(&mut self, _tick: T);
}
