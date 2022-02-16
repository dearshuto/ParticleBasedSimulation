use rapier3d::{prelude::*, na::Vector3};
use crate::algorithm::IAlgorithm;

pub struct RapierWorld<TAlgorithm: IAlgorithm>
{
    _algorithm: TAlgorithm,
    rigid_body_set: RigidBodySet,
    collider_set: ColliderSet,
    physics_pipeline: PhysicsPipeline,
    island_manager: IslandManager,
    broad_phase: BroadPhase,
    narrow_phase: NarrowPhase,
    joint_set: JointSet,
    ccd_solver: CCDSolver,
}

impl<TAlgorithm: IAlgorithm> RapierWorld<TAlgorithm> {
    pub fn new(algorithm: TAlgorithm) -> Self {
        let rigid_body = RigidBodyBuilder::new_static().build();
        let collider = ColliderBuilder::trimesh(vec![
            Point::<Real>::new(0.0, 0.0, 0.0),
            Point::<Real>::new(1.0, 0.0, 0.0),
            Point::<Real>::new(1.0, 0.0, 1.0),
        ], vec![[0, 1, 2]]).build();

        let mut rigid_body_set = RigidBodySet::new();
        let mut collider_set = ColliderSet::new();
        let rigid_body_handle = rigid_body_set.insert(rigid_body);
        let _collider_handle = collider_set.insert_with_parent(collider, rigid_body_handle, &mut rigid_body_set);

        Self {
            _algorithm: algorithm,
            rigid_body_set: rigid_body_set,
            collider_set: collider_set,
            physics_pipeline: PhysicsPipeline::new(),
            island_manager: IslandManager::new(),
            broad_phase: BroadPhase::new(),
            narrow_phase: NarrowPhase::new(),
            joint_set: JointSet::new(),
            ccd_solver: CCDSolver::new(),
        }
    }

    pub fn add_particle(&mut self, position: Vector3<f32>, radius: f32) {
        let ridid_body = RigidBodyBuilder::new_dynamic().translation(position).build();
        let collider = ColliderBuilder::ball(radius).build();
        let handle = self.rigid_body_set.insert(ridid_body);
        let _collider_handle = self.collider_set.insert_with_parent(collider, handle, &mut self.rigid_body_set);
    }

    pub fn execute<T>(&mut self, _tick: T) {
        let gravity = vector![0.0, -9.8, 0.0];
        let integration_parameters = IntegrationParameters::default();
        let physics_hooks = ();
        let event_handler = ();
        self.physics_pipeline.step(&gravity, &integration_parameters,
                                   &mut self.island_manager,
                                   &mut self.broad_phase,
                                   &mut self.narrow_phase,
                                   &mut self.rigid_body_set,
                                   &mut self.collider_set,
                                   &mut self.joint_set,
                                   &mut self.ccd_solver, &physics_hooks, &event_handler)
    }

    pub fn get_position(&self)  -> Vector3<Real>{
        let (_, handle) = self.rigid_body_set.get_unknown_gen(1).unwrap();
        let rigid_body = self.rigid_body_set.get(handle).unwrap();
        *rigid_body.translation()
    }
}

