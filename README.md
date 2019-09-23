# Ray Tracer

* A very simple ray tracer, which is basically a ray tracer following Peter Shirley's "Ray Tracing in One Weekend" tutorial with some improvements.

## Results

* Scene from "Rat Tracing : The Next Week"
    * (1920x1080, 3000spp with random_in_sphere lambertian)
![output result](/output_images/final_1920_3000spp.png)

* Triangle Mesh (Bunny)
    * (800x800, 300 spp, 1.0f lambertian with random_in_sphere)
![output result](/output_images/rabbit_random_in_sphere.png)
    * (800x800, 300 spp, 1.0f lambertian with random_on_sphere)
![output result](/output_images/rabbit_random_on_sphere.png)
![output result](/output_images/rabbit_random_on_sphere2.png)
    * (800x800, 300 spp, albedo : white, fuzziness : 0.0f metal with random_on_sphere)
![output result](/output_images/rabbit_random_on_sphere_metal.png)