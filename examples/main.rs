use kiss3d;
use kiss3d::window::Window;
use kiss3d::light::Light;

fn main() {
    let algorithm = sjps::algorithm::SimpleSmoothedParticleHydrodymamics{};
    let mut world = sjps::world::RapierWorld::new(algorithm);
    world.add_particle(rapier3d::na::Vector3::new(0.0, 50.0, 0.0), 0.5);

    let mut window = Window::new("Hello Simulation");
    let mut cube      = window.add_cube(10.0, 0.05, 10.0);
    cube.set_color(1.0, 1.0, 1.0);

    let mut sphere = window.add_sphere(0.5);
    window.set_light(Light::StickToCamera);

//    let rot = UnitQuaternion::from_axis_angle(&Vector3::y_axis(), 0.014);

    let mut inverse_position = kiss3d::nalgebra::Translation3::new(0.0, 0.0, 0.0);
    while window.render() {
        world.execute(1.0/10.0);

        let position = world.get_position();
        let translation = kiss3d::nalgebra::Translation3::new(position[0], position[1], position[2]);
        sphere.append_translation(&inverse_position);
        sphere.append_translation(&translation);
        inverse_position = translation.inverse();
    }
}
