// povchem.inc -- Pov-Ray include file for use with PovChem
// by Shmoot, 2017

#version 3.5;

global_settings
{
  assumed_gamma srgb
  charset utf8  // to get some Greek characters in text objects
}

// rough contents of this file:
// - constant and string declarations
// - background objects
// - atom object definitions
// - reactor object definitions
// - special effects -- device and I/O pad flashes and the like

// clock will tick once per reaction cycle.  For cycle 1, clock will run [0, 1); for cycle 2, [1, 2); etc.
#declare mod_clock = (mod(clock, 1));  // get a variable from 0 to 1 for each frame of a cycle
#declare quad_expand = (1 - pow((1 - mod_clock), 2));  // quadratic scale up from [0, 1); starts steep, ends level
#declare cubic_expand = (1 - pow((1 - mod_clock), 3));  // cubic scale up from [0, 1); starts steep, ends level
#declare cubic_contract = (1 - pow(mod_clock, 3));  // cubic scale down from [1, 0); starts level, ends steep
#declare sine_expand = ((-(cos(pi * mod_clock)) + 1) / 2);  // sinusoidal scale up from [0, 1); starts and ends level, steep in middle

#declare red_color = rgb<1, 0.025, 0.075>;
#declare blue_color = rgb<0.3, 0.3, 1>;

#declare red_tex = texture
{
  pigment {red_color}
  finish
  {
    ambient 0.35
    // reflection 0.3
    specular 0.4
    roughness 0.025
    metallic
  }
}

#declare blue_tex = texture
{
  pigment {blue_color}
  finish
  {
    ambient 0.35
    // reflection 0.3
    specular 0.4
    roughness 0.025
    metallic
  }
}

#declare dull_red_tex = texture
{
  // pigment {red_color * 0.75}
  pigment {red_color * 0.65}
  finish {ambient 0.35}
}

#declare dull_blue_tex = texture
{
  // pigment {blue_color * 0.65}
  pigment {blue_color * 0.55}
  finish {ambient 0.35}
}

#declare white_tex = texture
{
  pigment {rgb 1}
  finish {ambient 0.35}
}

#declare dull_white_tex = texture
{
  // pigment {rgb 0.75}
  pigment {rgb 0.55}
  finish {ambient 0.35}
}

#declare gray_tex = texture
{
  pigment {rgb 0.5}
  finish {ambient 0.35}
}
#declare grey_tex = gray_tex

#declare dull_gray_tex = texture
{
  pigment {rgb 0.35}
  finish {ambient 0.35}
}
#declare dull_grey_tex = dull_gray_tex

#declare black_tex = texture
{
  pigment {rgb 0}
  finish {ambient 0.35}
}

#declare silvery_tex = texture
{
  pigment {rgb 0.65}
  finish
  {
    ambient 0.35
    specular 0.4
    roughness 0.025
    metallic
  }
}

#declare plain_red_tex = texture {pigment {red_color} finish {ambient 0.35}}
#declare plain_blue_tex = texture {pigment {blue_color} finish {ambient 0.35}}


#declare letter_alpha = "\u03b1"
#declare letter_beta = "\u03b2"
#declare letter_psi = "\u03c8"
#declare letter_omega_small = "\u03c9"

#declare letter_Delta = "\u0394"
#declare letter_Theta = "\u0398"
#declare letter_Sigma = "\u03a3"
#declare letter_Omega_large = "\u03a9"

#declare grid_layer = 2;  // the tiled background of the scene
#declare device_layer = 1;  // bonders, sensors, laser targets, etc.
#declare atom_layer = 0;  // atoms and the bonds between them
#declare waldo_layer = -1;
#declare blue_layer = -2;  // blue tracks
#declare blue_control_layer = (blue_layer - 0.5);  // blue reactor controls
#declare red_layer = -3;  // red tracks
#declare red_control_layer = (red_layer - 0.5);  // red reactor controls
#declare screen_layer = -4;  // a feature to hide excess track
#declare label_grid_layer = -4.2;
#declare label_atom_layer = -4.5;
#declare atom_min_radius = 0.375;
#declare atom_max_radius = 0.45;

#declare red_pad_flash_intersect = box {<-5, -4, 1.86>, <5, 4, 1.87>}
#declare blue_pad_flash_intersect = box {<-5, -4, 1.88>, <5, 4, 1.89>}

#declare red_sfx_intersect = box {<-10, -4, 0.96>, <5, 4, 0.97>}
#declare blue_sfx_intersect = box {<-10, -4, 0.98>, <5, 4, 0.99>}

#declare red_bond_report_intersect = box {<-5, -4, -3.78>, <5, 4, -3.77>}
#declare blue_bond_report_intersect = box {<-5, -4, -3.76>, <5, 4, -3.75>}

#declare gridbox = union
{
  box {<0.04, 0.04, 0>, <0.96, 0.96, 0.05>}
  cylinder {<0.04, 0.04, 0.025>, <0.96, 0.04, 0.025>, 0.025}
  cylinder {<0.04, 0.04, 0.025>, <0.04, 0.96, 0.025>, 0.025}
  cylinder {<0.04, 0.96, 0.025>, <0.96, 0.96, 0.025>, 0.025}
  cylinder {<0.96, 0.04, 0.025>, <0.96, 0.96, 0.025>, 0.025}
  sphere {<0.04, 0.04, 0.025>, 0.025}
  sphere {<0.96, 0.04, 0.025>, 0.025}
  sphere {<0.04, 0.96, 0.025>, 0.025}
  sphere {<0.96, 0.96, 0.025>, 0.025}
  no_shadow
}

#declare plain_grid_tex = texture
{
  pigment{rgb 0.11}
  finish {ambient 0.35}
}

#declare beta_psi_tex = texture
{
  pigment {rgb 0.15}
  finish {ambient 0.35}
}

#declare alpha_omega_tex = texture
{
  pigment {rgb 0.19}
  finish {ambient 0.35}
}

#declare label_texture = texture
{
  pigment {rgb 0.3}
  finish {ambient 0.35}
}

light_source {<10, 10, -10> rgb 0.5}
light_source {<-10, 0, -10> rgb 0.5}
light_source {<0, -10, -10> rgb 0.5}


#declare grid_section = union
{
  object {gridbox translate <0, 0, grid_layer>}
  object {gridbox translate <0, 1, grid_layer>}
  object {gridbox translate <0, 2, grid_layer>}
  object {gridbox translate <0, 3, grid_layer>}
  object {gridbox translate <-1, 0, grid_layer>}
  object {gridbox translate <-1, 1, grid_layer>}
  object {gridbox translate <-1, 2, grid_layer>}
  object {gridbox translate <-1, 3, grid_layer>}
}

// middle
union
{
  object {grid_section}
  object {grid_section translate <0, -4, 0>}
  texture {plain_grid_tex}
}

// input alpha
union
{
  object {grid_section translate <-4, 0, 0>}
  object {grid_section translate <-2, 0, 0>}
  texture {alpha_omega_tex}
}

union
{
  text {ttf "times.ttf" letter_alpha 0.1 0 scale <2.5, 2.5, 1> translate <0.45, 0.65, 0>}
  text {ttf "cyrvetic.ttf" "input" 0.1 0 scale <0.4, 0.4, 1> translate <0.6, 0.2, 0>}
  texture {label_texture}
  translate <-4, 1, grid_layer - 0.1>
  no_shadow
}

// input beta
union
{
  object {grid_section translate <-4, -4, 0>}
  object {grid_section translate <-2, -4, 0>}
  texture {beta_psi_tex}
}

union
{
  text {ttf "times.ttf" letter_beta 0.1 0 scale <2, 2, 1> translate <0.6, 0.5, 0>}
  text {ttf "cyrvetic.ttf" "input" 0.1 0 scale <0.4, 0.4, 1> translate <0.85, 0.2, 0>}
  texture {label_texture}
  translate <-4, -3, grid_layer - 0.1>
  no_shadow
}

// output psi
#declare output_psi = union
{
  union
  {
    object {grid_section translate <2, 0, 0>}
    object {grid_section translate <4, 0, 0>}
    texture {beta_psi_tex}
  }
  union
  {
    text {ttf "times.ttf" letter_psi 0.1 0 scale <2, 2, 1> translate <0.4, 1, 0>}
    text {ttf "cyrvetic.ttf" "output" 0.1 0 scale <0.4, 0.4, 1> translate <0.45, 0.2, 0>}
    texture {label_texture}
    translate <2, 1, grid_layer - 0.1>
  }
  no_shadow
}

// output omega
#declare output_omega = union
{
  union
  {
    object {grid_section translate <2, -4, 0>}
    object {grid_section translate <4, -4, 0>}
    texture {alpha_omega_tex}
  }
  union
  {
    text {ttf "times.ttf" letter_omega_small 0.1 0 scale <2.5, 2.5, 1> translate <0.27, 0.6, 0>}
    text {ttf "cyrvetic.ttf" "output" 0.1 0 scale <0.4, 0.4, 1> translate <0.45, 0.2, 0>}
    texture {label_texture}
    translate <2, -3, grid_layer - 0.1>
  }
  no_shadow
}

// large psi output
#declare big_output_psi = union
{
  union
  {
    object {grid_section translate <2, 0, 0>}
    object {grid_section translate <4, 0, 0>}
    object {grid_section translate <2, -4, 0>}
    object {grid_section translate <4, -4, 0>}
    texture {alpha_omega_tex}
  }
  union
  {
    text {ttf "times.ttf" letter_psi 0.1 0 scale <2, 2, 1> translate <0.4, 1, 0>}
    text {ttf "cyrvetic.ttf" "output" 0.1 0 scale <0.4, 0.4, 1> translate <0.45, 0.2, 0>}
    texture {label_texture}
    translate <2, -1, grid_layer - 0.1>
  }
  no_shadow
}
// specify either big_output_psi or (output_psi and output_omega) in the scene file

// screen to block off any track that may stick out over the edge
difference
{
  box {<-100, -100, screen_layer>, <100, 100, screen_layer + 0.1>}
  box {<-5, -4, screen_layer - 5>, <5, 4, screen_layer + 5>}
  texture
  {
    pigment {rgb 0}
    finish {ambient 0}
  }
  no_shadow
}

// lots of atom declarations

// 1 Hydrogen
#declare H_base = sphere {<0, 0, 0>, (atom_min_radius + (((1 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare H_letter = text {ttf "cyrvetic.ttf" "H" 20 0 scale 0.7 translate <0.3 - 0.5, 0.25 - 0.5, -5>}
#declare H_atom = union
{
  difference
  {
    object {H_base} object {H_letter}
    texture
    {
      pigment {rgb 1}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {H_base} object {H_letter}
    texture
    {
      pigment {rgb 0}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 2 Helium
#declare He_base = sphere {<0, 0, 0>, (atom_min_radius + (((2 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare He_letter = text {ttf "cyrvetic.ttf" "He" 20 0 scale 0.55 translate <0.21 - 0.5, 0.3 - 0.5, -5>}
#declare He_atom = union
{
  difference
  {
    object {He_base} object {He_letter}
    texture
    {
      pigment {rgb <0.9, 0.2, 0>}
      finish {ambient 0.6}
    }
  }
  intersection
  {
    object {He_base} object {He_letter}
    texture
    {
      pigment {rgb .9}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 3 Lithium
#declare Li_base = sphere {<0, 0, 0>, (atom_min_radius + (((3 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Li_letter = text {ttf "cyrvetic.ttf" "Li" 20 0 scale 0.7 translate <0.27 - 0.5, 0.25 - 0.5, -5>}
#declare Li_atom = union
{
  difference
  {
    object {Li_base} object {Li_letter}
    texture
    {
      pigment {rgb <0.8, 0.8, 0.8>}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Li_base} object {Li_letter}
    texture
    {
      pigment {rgb <0.2, 0.2, 0.2>}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 4 Beryllium
#declare Be_base = sphere {<0, 0, 0>, (atom_min_radius + (((4 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Be_letter = text {ttf "cyrvetic.ttf" "Be" 20 0 scale 0.57 translate <0.22 - 0.5, 0.29 - 0.5, -5>}
#declare Be_atom = union
{
  difference
  {
    object {Be_base} object {Be_letter}
    texture
    {
      pigment {rgb <0.5, 0.5, 0.5>}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Be_base} object {Be_letter}
    texture
    {
      pigment {rgb <0.1, 0.1, 0.1>}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 5 Boron
#declare B_base = sphere {<0, 0, 0>, (atom_min_radius + (((5 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare B_letter = text {ttf "cyrvetic.ttf" "B" 20 0 scale 0.8 translate <0.32 - 0.5, 0.22 - 0.5, -5>}
#declare B_atom = union
{
  difference
  {
    object {B_base} object {B_letter}
    texture
    {
      pigment {rgb <0.3, 0.2, 0.15>}
      finish {ambient 0.35 specular 0.8 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {B_base} object {B_letter}
    texture
    {
      pigment {rgb 0.05}
      finish {ambient 0.35 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 6 Carbon
#declare C_base = sphere {<0, 0, 0>, (atom_min_radius + (((6 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare C_letter = text {ttf "cyrvetic.ttf" "C" 20 0 scale 0.8 translate <0.235 - 0.5, 0.21 - 0.5, -5>}
#declare C_atom = union
{
  difference
  {
    object {C_base} object {C_letter}
    texture
    {
      pigment {rgb <0.08, 0.08, 0.08>}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {C_base} object {C_letter}
    texture
    {
      pigment {rgb <1, 1, 1>}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 7 Nitrogen
#declare N_base = sphere {<0, 0, 0>, (atom_min_radius + (((7 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare N_letter = text {ttf "cyrvetic.ttf" "N" 20 0 scale 0.75 translate <0.29 - 0.5, 0.23 - 0.5, -5>}
#declare N_atom = union
{
  difference
  {
    object {N_base} object {N_letter}
    texture
    {
      pigment {rgb <1, 1, 1>}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {N_base} object {N_letter}
    texture
    {
      pigment {rgb <0.7, 0.7, 0.7>}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 8 Oxygen
#declare O_base = sphere {<0, 0, 0>, (atom_min_radius + (((8 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare O_letter = text {ttf "cyrvetic.ttf" "O" 20 0 scale 0.75 translate <0.245 - 0.5, 0.225 - 0.5, -5>}
#declare O_atom = union
{
  difference
  {
    object {O_base} object {O_letter}
    texture
    {
      pigment {rgb <0.7, 0.8, 1>}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {O_base} object {O_letter}
    texture
    {
      pigment {rgb <0.3, 0.3, 0.3>}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 9 Fluorine
#declare F_base = sphere {<0, 0, 0>, (atom_min_radius + (((9 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare F_letter = text {ttf "cyrvetic.ttf" "F" 20 0 scale 0.8 translate <0.32 - 0.5, 0.21 - 0.5, -5>}
#declare F_atom = union
{
  difference
  {
    object {F_base} object {F_letter}
    texture
    {
      pigment {rgb <1, 1, 0.6>}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {F_base} object {F_letter}
    texture
    {
      pigment {rgb <0.4, 0.4, 0.2>}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 10 Neon
#declare Ne_base = sphere {<0, 0, 0>, (atom_min_radius + (((10 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ne_letter = text {ttf "cyrvetic.ttf" "Ne" 20 0 scale 0.55 translate <0.2 - 0.5, 0.3 - 0.5, -5>}
#declare Ne_atom = union
{
  difference
  {
    object {Ne_base} object {Ne_letter}
    texture
    {
      pigment {rgb <0.98, 0.3, 0.2>}
      finish {ambient 0.5}
    }
  }
  intersection
  {
    object {Ne_base} object {Ne_letter}
    texture
    {
      pigment {rgb <0.8, 0.8, 0.8>}
      finish {ambient 0.25}
    }
  }
  no_shadow
}

// 11 Sodium
#declare Na_base = sphere {<0, 0, 0>, (atom_min_radius + (((11 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Na_letter = text {ttf "cyrvetic.ttf" "Na" 20 0 scale 0.52 translate <-0.3, -0.18, -5>}
#declare Na_atom = union
{
  difference
  {
    object {Na_base} object {Na_letter}
    texture
    {
      pigment {rgb 0.8}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Na_base} object {Na_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 12 Magnesium
#declare Mg_base = sphere {<0, 0, 0>, (atom_min_radius + (((12 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Mg_letter = text {ttf "cyrvetic.ttf" "Mg" 20 0 scale 0.47 translate <-0.3, -0.16, -5>}
#declare Mg_atom = union
{
  difference
  {
    object {Mg_base} object {Mg_letter}
    texture
    {
      pigment {rgb 0.8}
      finish {ambient 0.35 reflection 0.6 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Mg_base} object {Mg_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35 reflection 0.6 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 13 Aluminum
#declare Al_base = sphere {<0, 0, 0>, (atom_min_radius + (((13 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Al_letter = text {ttf "cyrvetic.ttf" "Al" 20 0 scale 0.65 translate <-0.5 + 0.2, -0.5 + 0.28, -5>}
#declare Al_atom = union
{
  difference
  {
    object {Al_base} object {Al_letter}
    texture
    {
      pigment {rgb 0.9}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Al_base} object {Al_letter}
    texture
    {
      pigment {rgb 0.4}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 14 Silicon
#declare Si_base = sphere {<0, 0, 0>, (atom_min_radius + (((14 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Si_letter = text {ttf "cyrvetic.ttf" "Si" 20 0 scale 0.65 translate <-0.5 + 0.23, -0.5 + 0.25, -5>}
#declare Si_atom = union
{
  difference
  {
    object {Si_base} object {Si_letter}
    texture
    {
      pigment {rgb <0.6, 0.6, 1>}
      finish {ambient 0.35 reflection 0.4 specular 0.8 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Si_base} object {Si_letter}
    texture
    {
      pigment {rgb 0.3}
      finish {ambient 0.35 reflection 0.4 specular 0.8 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 15 Phosphorus
#declare P_base = sphere {<0, 0, 0>, (atom_min_radius + (((15 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare P_letter = text {ttf "cyrvetic.ttf" "P" 20 0 scale 0.8 translate <-0.5 + 0.33, -0.5+ 0.2, -5>}
#declare P_atom = union
{
  difference
  {
    object {P_base} object {P_letter}
    texture
    {
      pigment {rgb <0.8, 0.1, 0.1>}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {P_base} object {P_letter}
    texture
    {
      pigment {rgb <0.2, 0.0, 0.0>}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 16 Sulfur
#declare S_base = sphere {<0, 0, 0>, (atom_min_radius + (((16 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare S_letter = text {ttf "cyrvetic.ttf" "S" 20 0 scale 0.7 translate <-0.5 + 0.31, -0.5 + 0.25, -5>}
#declare S_atom = union
{
  difference
  {
    object {S_base} object {S_letter}
    texture
    {
      pigment {rgb <0.87, 0.9, 0.1>}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {S_base} object {S_letter}
    texture
    {
      pigment {rgb <0.4, 0.4, 0>}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 17 Chlorine
#declare Cl_base = sphere {<0, 0, 0>, (atom_min_radius + (((17 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Cl_letter = text {ttf "cyrvetic.ttf" "Cl" 20 0 scale 0.65 translate <-0.5 + 0.21, -0.5 + 0.26, -5>}
#declare Cl_atom = union
{
  difference
  {
    object {Cl_base} object {Cl_letter}
    texture
    {
      pigment {rgb <0.8, 0.95, 0.5>}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {Cl_base} object {Cl_letter}
    texture
    {
      pigment {rgb <0.8, 0.95, 0.5> * 0.4}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 18 Argon
#declare Ar_base = sphere {<0, 0, 0>, (atom_min_radius + (((18 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ar_letter = text {ttf "cyrvetic.ttf" "Ar" 20 0 scale 0.65 translate <-0.5 + 0.19, -0.5 + 0.3, -5>}
#declare Ar_atom = union
{
  difference
  {
    object {Ar_base} object {Ar_letter}
    texture
    {
      pigment {rgb <0.8, 0.4, 0.8>}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {Ar_base} object {Ar_letter}
    texture
    {
      pigment {rgb <0.8, 0.8, 0.8>}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 19 Potassium
#declare K_base = sphere {<0, 0, 0>, (atom_min_radius + (((19 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare K_letter = text {ttf "cyrvetic.ttf" "K" 20 0 scale 0.7 translate <-0.5 + 0.32, -0.5 + 0.25, -5>}
#declare K_atom = union
{
  difference
  {
    object {K_base} object {K_letter}
    texture
    {
      pigment {rgb 0.68}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.075 metallic}
    }
  }
  intersection
  {
    object {K_base} object {K_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.075 metallic}
    }
  }
  no_shadow
}

// 20 Calcium
#declare Ca_base = sphere {<0, 0, 0>, (atom_min_radius + (((20 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ca_letter = text {ttf "cyrvetic.ttf" "Ca" 20 0 scale 0.55 translate <-0.5 + 0.16, -0.5 + 0.3, -5>}
#declare Ca_atom = union
{
  difference
  {
    object {Ca_base} object {Ca_letter}
    texture
    {
      pigment {rgb <0.7, 0.7, 0.58>}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ca_base} object {Ca_letter}
    texture
    {
      pigment {rgb 0.3}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
  // rotate 45*y
}

// 21 Scandium
#declare Sc_base = sphere {<0, 0, 0>, (atom_min_radius + (((21 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Sc_letter = text {ttf "cyrvetic.ttf" "Sc" 20 0 scale 0.6 translate <-0.5 + 0.17, -0.5 + 0.27, -5>}
#declare Sc_atom = union
{
  difference
  {
    object {Sc_base} object {Sc_letter}
    texture
    {
      pigment {rgb 0.72}
      finish {ambient 0.35 reflection 0.33 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Sc_base} object {Sc_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.33 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 22 Titanium
#declare Ti_base = sphere {<0, 0, 0>, (atom_min_radius + (((22 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ti_letter = text {ttf "cyrvetic.ttf" "Ti" 20 0 scale 0.7 translate <-0.5 + 0.2, -0.5 + 0.21, -5>}
#declare Ti_atom = union
{
  difference
  {
    object {Ti_base} object {Ti_letter}
    texture
    {
      pigment {rgb 0.75}
      finish {ambient 0.35 reflection 0.45 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ti_base} object {Ti_letter}
    texture
    {
      pigment {rgb 0.08}
      finish {ambient 0.35 reflection 0.45 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 23 Vanadium
#declare V_base = sphere {<0, 0, 0>, (atom_min_radius + (((23 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare V_letter = text {ttf "cyrvetic.ttf" "V" 20 0 scale 0.7 translate <-0.5 + 0.285, -0.5 + 0.23, -5>}
#declare V_atom = union
{
  difference
  {
    object {V_base} object {V_letter}
    texture
    {
      pigment {rgb <0.6, 0.6, 0.65>}
      finish {ambient 0.35 reflection 0.15 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {V_base} object {V_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35 reflection 0.15 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 24 Chromium
#declare Cr_base = sphere {<0, 0, 0>, (atom_min_radius + (((24 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Cr_letter = text {ttf "cyrvetic.ttf" "Cr" 20 0 scale 0.7 translate <-0.5 + 0.16, -0.5 + 0.25, -5>}
#declare Cr_atom = union
{
  difference
  {
    object {Cr_base} object {Cr_letter}
    texture
    {
      pigment {rgb <1, 1, 1>}
      finish {ambient 0.35 reflection 0.95 specular 0.4 roughness 0.015 metallic}
    }
  }
  intersection
  {
    object {Cr_base} object {Cr_letter}
    texture
    {
      pigment {rgb 0.3}
      finish {ambient 0.35 reflection 0.95 specular 0.4 roughness 0.015 }
    }
  }
  no_shadow
}

// 25 Manganese
#declare Mn_base = sphere {<0, 0, 0>, (atom_min_radius + (((25 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Mn_letter = text {ttf "cyrvetic.ttf" "Mn" 20 0 scale 0.50 translate <-0.5 + 0.2, -0.5 + 0.31, -5>}
#declare Mn_atom = union
{
  difference
  {
    object {Mn_base} object {Mn_letter}
    texture
    {
      pigment {rgb 0.55}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Mn_base} object {Mn_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 26 Iron
#declare Fe_base = sphere {<0, 0, 0>, (atom_min_radius + (((26 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Fe_letter = text {ttf "cyrvetic.ttf" "Fe" 20 0 scale 0.6 translate <-0.5 + 0.23, -0.5 + 0.28, -5>}
#declare Fe_atom = union
{
  difference
  {
    object {Fe_base} object {Fe_letter}
    texture
    {
      // pigment {rgb 0.45}
      pigment {rgb <0.4, 0.08, 0>}
      finish {ambient 0.35 reflection 0.1 specular 0.6 roughness 0.06 metallic}
    }
  }
  intersection
  {
    object {Fe_base} object {Fe_letter}
    texture
    {
      // pigment {rgb <0.4, 0.08, 0>}
      pigment {rgb 0.05}
      finish {ambient 0.35 reflection 0.1 specular 0.2 roughness 0.06}
    }
  }
  no_shadow
}

// 27 Cobalt
#declare Co_base = sphere {<0, 0, 0>, (atom_min_radius + (((27 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Co_letter = text {ttf "cyrvetic.ttf" "Co" 20 0 scale 0.58 translate <-0.5 + 0.16, -0.5 + 0.28, -5>}
#declare Co_atom = union
{
  difference
  {
    object {Co_base} object {Co_letter}
    texture
    {
      pigment {rgb <0, 0.278, 0.671>}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Co_base} object {Co_letter}
    texture
    {
      pigment {rgb <0, 0.278, 0.671> * 0.3}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 28 Nickel
#declare Ni_base = sphere {<0, 0, 0>, (atom_min_radius + (((28 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ni_letter = text {ttf "cyrvetic.ttf" "Ni" 20 0 scale 0.65 translate <-0.5 + 0.24, -0.5 + 0.26, -5>}
#declare Ni_atom = union
{
  difference
  {
    object {Ni_base} object {Ni_letter}
    texture
    {
      pigment {rgb <0.9, 0.87, 0.74>}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ni_base} object {Ni_letter}
    texture
    {
      pigment {rgb <0.9, 0.87, 0.74> * 0.2}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 29 Copper
#declare Cu_base = sphere {<0, 0, 0>, (atom_min_radius + (((29 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Cu_letter = text {ttf "cyrvetic.ttf" "Cu" 20 0 scale 0.56 translate <-0.5 + 0.168, -0.5 + 0.29, -5>}
#declare Cu_atom = union
{
  difference
  {
    object {Cu_base} object {Cu_letter}
    texture
    {
      // pigment {rgb <0.94, 0.335, 0.05>}
      pigment {rgb <0.94, 0.4, 0.05>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Cu_base} object {Cu_letter}
    texture
    {
      pigment {rgb <0.263, 0.702, 0.682>}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 30 Zinc
#declare Zn_base = sphere {<0, 0, 0>, (atom_min_radius + (((30 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Zn_letter = text {ttf "cyrvetic.ttf" "Zn" 20 0 scale 0.55 translate <-0.5 + 0.20, -0.5 + 0.3, -5>}
#declare Zn_atom = union
{
  difference
  {
    object {Zn_base} object {Zn_letter}
    texture
    {
      pigment {rgb 0.65}
      finish {ambient 0.35 reflection 0.15 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Zn_base} object {Zn_letter}
    texture
    {
      pigment {rgb 0.18}
      finish {ambient 0.35 reflection 0.15 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 31 Gallium
#declare Ga_base = sphere {<0, 0, 0>, (atom_min_radius + (((31 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ga_letter = text {ttf "cyrvetic.ttf" "Ga" 20 0 scale 0.55 translate <-0.5 + 0.15, -0.5 + 0.3, -5>}
#declare Ga_atom = union
{
  difference
  {
    object {Ga_base} object {Ga_letter}
    texture
    {
      pigment {rgb <0.7, 0.7, 0.8>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ga_base} object {Ga_letter}
    texture
    {
      pigment {rgb <0.7, 0.7, 0.8> * 0.3}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 32 Germanium
#declare Ge_base = sphere {<0, 0, 0>, (atom_min_radius + (((32 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ge_letter = text {ttf "cyrvetic.ttf" "Ge" 20 0 scale 0.55 translate <-0.5 + 0.17, -0.5 + 0.3, -5>}
#declare Ge_atom = union
{
  difference
  {
    object {Ge_base} object {Ge_letter}
    texture
    {
      pigment {rgb 0.7}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ge_base} object {Ge_letter}
    texture
    {
      pigment {rgb 0.05}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 33 Arsenic
#declare As_base = sphere {<0, 0, 0>, (atom_min_radius + (((33 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare As_letter = text {ttf "cyrvetic.ttf" "As" 20 0 scale 0.56 translate <-0.5 + 0.195, -0.5 + 0.31, -5>}
#declare As_atom = union
{
  difference
  {
    object {As_base} object {As_letter}
    texture
    {
      pigment {rgb <0.8, 0.8, 0.65>}
      finish {ambient 0.35 reflection 0.15 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {As_base} object {As_letter}
    texture
    {
      pigment {rgb 0.12}
      finish {ambient 0.35 reflection 0.15 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 34 Selenium
#declare Se_base = sphere {<0, 0, 0>, (atom_min_radius + (((34 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Se_letter = text {ttf "cyrvetic.ttf" "Se" 20 0 scale 0.57 translate <-0.5 + 0.19, -0.5 + 0.29, -5>}
#declare Se_atom = union
{
  difference
  {
    object {Se_base} object {Se_letter}
    texture
    {
      pigment {rgb 0.35}
      finish {ambient 0.35 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Se_base} object {Se_letter}
    texture
    {
      pigment {rgb <0.75, 0, 0.05>}
      finish {ambient 0.35 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 35 Bromine
#declare Br_base = sphere {<0, 0, 0>, (atom_min_radius + (((35 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Br_letter = text {ttf "cyrvetic.ttf" "Br" 20 0 scale 0.65 translate <-0.5 + 0.24, -0.5 + 0.26, -5>}
#declare Br_atom = union
{
  difference
  {
    object {Br_base} object {Br_letter}
    texture
    {
      pigment {rgb <0.9, 0.18, 0.05> * 0.8}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {Br_base} object {Br_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 36 Krypton
#declare Kr_base = sphere {<0, 0, 0>, (atom_min_radius + (((36 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Kr_letter = text {ttf "cyrvetic.ttf" "Kr" 20 0 scale 0.65 translate <-0.5 + 0.23, -0.5 + 0.26, -5>}
#declare Kr_atom = union
{
  difference
  {
    object {Kr_base} object {Kr_letter}
    texture
    {
      pigment {rgb 1.2}
      finish {ambient 0.35}
    }
  }
  intersection
  {
    object {Kr_base} object {Kr_letter}
    texture
    {
      pigment {rgb 0.8}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 37 Rubidium
#declare Rb_base = sphere {<0, 0, 0>, (atom_min_radius + (((37 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Rb_letter = text {ttf "cyrvetic.ttf" "Rb" 20 0 scale 0.56 translate <-0.5 + 0.21, -0.5 + 0.30, -5>}
#declare Rb_atom = union
{
  difference
  {
    object {Rb_base} object {Rb_letter}
    texture
    {
      pigment {rgb 0.7}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Rb_base} object {Rb_letter}
    texture
    {
      pigment {rgb 0.18}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 38 Strontium
#declare Sr_base = sphere {<0, 0, 0>, (atom_min_radius + (((38 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Sr_letter = text {ttf "cyrvetic.ttf" "Sr" 20 0 scale 0.65 translate <-0.5 + 0.21, -0.5 + 0.26, -5>}
#declare Sr_atom = union
{
  difference
  {
    object {Sr_base} object {Sr_letter}
    texture
    {
      pigment {rgb <0.95, 0.9, 0.5>}
      finish {ambient 0.35 reflection 0.3 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Sr_base} object {Sr_letter}
    texture
    {
      pigment {rgb <0.95, 0.9, 0.5> * 0.3}
      finish {ambient 0.35 reflection 0.3 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 39 Yttrium
#declare Y_base = sphere {<0, 0, 0>, (atom_min_radius + (((39 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Y_letter = text {ttf "cyrvetic.ttf" "Y" 20 0 scale 0.7 translate <-0.5 + 0.28, -0.5 + 0.23, -5>}
#declare Y_atom = union
{
  difference
  {
    object {Y_base} object {Y_letter}
    texture
    {
      pigment {rgb 0.9}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Y_base} object {Y_letter}
    texture
    {
      pigment {rgb 0.5}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 40 Zirconium
#declare Zr_base = sphere {<0, 0, 0>, (atom_min_radius + (((40 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Zr_letter = text {ttf "cyrvetic.ttf" "Zr" 20 0 scale 0.65 translate <-0.5 + 0.23, -0.5 + 0.26, -5>}
#declare Zr_atom = union
{
  difference
  {
    object {Zr_base} object {Zr_letter}
    texture
    {
      pigment {rgb 0.8}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Zr_base} object {Zr_letter}
    texture
    {
      pigment {rgb 0.3}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 41 Niobium
#declare Nb_base = sphere {<0, 0, 0>, (atom_min_radius + (((41 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Nb_letter = text {ttf "cyrvetic.ttf" "Nb" 20 0 scale 0.55 translate <-0.5 + 0.2, -0.5 + 0.3, -5>}
#declare Nb_atom = union
{
  difference
  {
    object {Nb_base} object {Nb_letter}
    texture
    {
      pigment {rgb 0.5}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.035 metallic}
    }
  }
  intersection
  {
    object {Nb_base} object {Nb_letter}
    texture
    {
      pigment {rgb <0.2, 0.2, 0.5>}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.035 metallic}
    }
  }
  no_shadow
}

// 42 Molybdenum
#declare Mo_base = sphere {<0, 0, 0>, (atom_min_radius + (((42 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Mo_letter = text {ttf "cyrvetic.ttf" "Mo" 20 0 scale 0.55 translate <-0.5 + 0.175, -0.5 + 0.3, -5>}
#declare Mo_atom = union
{
  difference
  {
    object {Mo_base} object {Mo_letter}
    texture
    {
      pigment {rgb 0.6}
      finish {ambient 0.35 reflection 0.3 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Mo_base} object {Mo_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35 reflection 0.3 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 43 Technetium
#declare Tc_base = sphere {<0, 0, 0>, (atom_min_radius + (((43 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Tc_letter = text {ttf "cyrvetic.ttf" "Tc" 20 (-0.08 * x) scale 0.6 translate <-0.5 + 0.19, -0.5 + 0.27, -5>}
#declare Tc_atom = union
{
  difference
  {
    object {Tc_base} object {Tc_letter}
    texture
    {
      pigment {rgb 0.62}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Tc_base} object {Tc_letter}
    texture
    {
      pigment {rgb 0.19}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 44 Ruthenium
#declare Ru_base = sphere {<0, 0, 0>, (atom_min_radius + (((44 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ru_letter = text {ttf "cyrvetic.ttf" "Ru" 20 0 scale 0.55 translate <-0.5 + 0.21, -0.5 + 0.3, -5>}
#declare Ru_atom = union
{
  difference
  {
    object {Ru_base} object {Ru_letter}
    texture
    {
      pigment {rgb 0.7}
      finish {ambient 0.35 reflection 0.55 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ru_base} object {Ru_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.55 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 45 Rhodium
#declare Rh_base = sphere {<0, 0, 0>, (atom_min_radius + (((45 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Rh_letter = text {ttf "cyrvetic.ttf" "Rh" 20 0 scale 0.55 translate <-0.5 + 0.21, -0.5 + 0.3, -5>}
#declare Rh_atom = union
{
  difference
  {
    object {Rh_base} object {Rh_letter}
    texture
    {
      pigment {rgb 0.75}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Rh_base} object {Rh_letter}
    texture
    {
      pigment {rgb <0.5, 0.4, 0.4>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 46 Palladium
#declare Pd_base = sphere {<0, 0, 0>, (atom_min_radius + (((46 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Pd_letter = text {ttf "cyrvetic.ttf" "Pd" 20 (-0.1 * x) scale 0.6 translate <-0.5 + 0.22, -0.5 + 0.28, -5>}
#declare Pd_atom = union
{
  difference
  {
    object {Pd_base} object {Pd_letter}
    texture
    {
      pigment {rgb 0.87}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Pd_base} object {Pd_letter}
    texture
    {
      pigment {rgb 0.17}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 47 Silver
#declare Ag_base = sphere {<0, 0, 0>, (atom_min_radius + (((47 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ag_letter = text {ttf "cyrvetic.ttf" "Ag" 20 0 scale 0.55 translate <-0.5 + 0.165, -0.5 + 0.32, -5>}
#declare Ag_atom = union
{
  difference
  {
    object {Ag_base} object {Ag_letter}
    texture
    {
      pigment {rgb 1}
      finish {ambient 0.35 reflection 1 diffuse 0.5 specular 0.4 roughness 0.005 metallic}
    }
  }
  intersection
  {
    object {Ag_base} object {Ag_letter}
    texture
    {
      pigment {rgb 1}
      finish {ambient 0.35 reflection 1 diffuse 0 specular 0.4 roughness 0.005 metallic}
    }
  }
  no_shadow
}

// 48 Cadmium
#declare Cd_base = sphere {<0, 0, 0>, (atom_min_radius + (((48 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Cd_letter = text {ttf "cyrvetic.ttf" "Cd" 20 0 scale 0.55 translate <-0.5 + 0.17, -0.5 + 0.3, -5>}
#declare Cd_atom = union
{
  difference
  {
    object {Cd_base} object {Cd_letter}
    texture
    {
      pigment {rgb <0.8, 0.8, 0.85>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Cd_base} object {Cd_letter}
    texture
    {
      pigment {rgb <0.8, 0.8, 0.85> * 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 49 Indium
#declare In_base = sphere {<0, 0, 0>, (atom_min_radius + (((49 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare In_letter = text {ttf "cyrvetic.ttf" "In" 20 0 scale 0.7 translate <-0.5 + 0.28, -0.5 + 0.25, -5>}
#declare In_atom = union
{
  difference
  {
    object {In_base} object {In_letter}
    texture
    {
      pigment {rgb 0.8}
      finish {ambient 0.35 reflection 0.6 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {In_base} object {In_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.6 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 50 Tin
#declare Sn_base = sphere {<0, 0, 0>, (atom_min_radius + (((50 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Sn_letter = text {ttf "cyrvetic.ttf" "Sn" 20 0 scale 0.6 translate <-0.5 + 0.165, -0.5 + 0.27, -5>}
#declare Sn_atom = union
{
  difference
  {
    object {Sn_base} object {Sn_letter}
    texture
    {
      pigment {rgb 0.7}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Sn_base} object {Sn_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 51 Antimony
#declare Sb_base = sphere {<0, 0, 0>, (atom_min_radius + (((51 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Sb_letter = text {ttf "cyrvetic.ttf" "Sb" 20 0 scale 0.6 translate <-0.5 + 0.17, -0.5 + 0.28, -5>}
#declare Sb_atom = union
{
  difference
  {
    object {Sb_base} object {Sb_letter}
    texture
    {
      pigment {rgb 0.8}
      finish {ambient 0.35 reflection 0.6 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Sb_base} object {Sb_letter}
    texture
    {
      pigment {rgb 0.3}
      finish {ambient 0.35 reflection 0.6 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 52 Tellurium
#declare Te_base = sphere {<0, 0, 0>, (atom_min_radius + (((52 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Te_letter = text {ttf "cyrvetic.ttf" "Te" 20 0 scale 0.6 translate <-0.5 + 0.21, -0.5 + 0.28, -5>}
#declare Te_atom = union
{
  difference
  {
    object {Te_base} object {Te_letter}
    texture
    {
      pigment {rgb 0.6}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Te_base} object {Te_letter}
    texture
    {
      pigment {rgb <0.8, 0.2, 0> * 0.2}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 53 Iodine
#declare I_base = sphere {<0, 0, 0>, (atom_min_radius + (((53 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
// #declare I_letter = text {ttf "cyrvetic.ttf" "I" 20 0 scale 0.7 translate <-0.5 + 0.462, -0.5 + 0.25, -5>}
#declare I_letter = box{<-0.04, -0.275, -20>, <0.04, 0.275, 20>}
#declare I_atom = union
{
  difference
  {
    object {I_base} object {I_letter}
    texture
    {
      pigment {rgb <0.5, 0, 1>}
      finish {ambient 0.35 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {I_base} object {I_letter}
    texture
    {
      pigment {rgb <0.5, 0, 1> * 0.2}
      finish {ambient 0.35 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 54 Xenon
#declare Xe_base = sphere {<0, 0, 0>, (atom_min_radius + (((54 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Xe_letter = text {ttf "cyrvetic.ttf" "Xe" 20 (-0.05 * x) scale 0.6 translate <-0.5 + 0.2, -0.5 + 0.28, -5>}
#declare Xe_atom = union
{
  difference
  {
    object {Xe_base} object {Xe_letter}
    texture
    {
      pigment {rgb <0.6, 0.6, 1>}
      finish {ambient 0.35}  // {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Xe_base} object {Xe_letter}
    texture
    {
      pigment {rgb 0.9}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 55 Cesium
#declare Cs_base = sphere {<0, 0, 0>, (atom_min_radius + (((55 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Cs_letter = text {ttf "cyrvetic.ttf" "Cs" 20 0 scale 0.6 translate <-0.5 + 0.16, -0.5 + 0.28, -5>}
#declare Cs_atom = union
{
  difference
  {
    object {Cs_base} object {Cs_letter}
    texture
    {
      pigment {rgb <0.8, 0.78, 0.6>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Cs_base} object {Cs_letter}
    texture
    {
      pigment {rgb 0.08}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 56 Barium
#declare Ba_base = sphere {<0, 0, 0>, (atom_min_radius + (((56 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ba_letter = text {ttf "cyrvetic.ttf" "Ba" 20 0 scale 0.55 translate <-0.5 + 0.205, -0.5 + 0.295, -5>}
#declare Ba_atom = union
{
  difference
  {
    object {Ba_base} object {Ba_letter}
    texture
    {
      pigment {rgb <0.6, 0.6, 0.54>}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ba_base} object {Ba_letter}
    texture
    {
      pigment {rgb 0.12}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 57 Lanthanum
#declare La_base = sphere {<0, 0, 0>, (atom_min_radius + (((57 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare La_letter = text {ttf "cyrvetic.ttf" "La" 20 0 scale 0.6 translate <-0.5 + 0.21, -0.5 + 0.28, -5>}
#declare La_atom = union
{
  difference
  {
    object {La_base} object {La_letter}
    texture
    {
      pigment {rgb 0.7}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {La_base} object {La_letter}
    texture
    {
      pigment {rgb 0.22}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 58 Cerium
#declare Ce_base = sphere {<0, 0, 0>, (atom_min_radius + (((58 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ce_letter = text {ttf "cyrvetic.ttf" "Ce" 20 0 scale 0.6 translate <-0.5 + 0.15, -0.5 + 0.28, -5>}
#declare Ce_atom = union
{
  difference
  {
    object {Ce_base} object {Ce_letter}
    texture
    {
      pigment {rgb 0.6}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ce_base} object {Ce_letter}
    texture
    {
      pigment {rgb 0.15}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 59 Praseodymium
#declare Pr_base = sphere {<0, 0, 0>, (atom_min_radius + (((59 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Pr_letter = text {ttf "cyrvetic.ttf" "Pr" 20 0 scale 0.7 translate <-0.5 + 0.23, -0.5 + 0.25, -5>}
#declare Pr_atom = union
{
  difference
  {
    object {Pr_base} object {Pr_letter}
    texture
    {
      pigment {rgb <0.6, 0.65, 0.5>}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Pr_base} object {Pr_letter}
    texture
    {
      pigment {rgb 0.15}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}
 
// 60 Neodymium
#declare Nd_base = sphere {<0, 0, 0>, (atom_min_radius + (((60 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Nd_letter = text {ttf "cyrvetic.ttf" "Nd" 20 0 scale 0.55 translate <-0.5 + 0.195, -0.5 + 0.3, -5>}
#declare Nd_atom = union
{
  difference
  {
    object {Nd_base} object {Nd_letter}
    texture
    {
      pigment {rgb <1, 0.5, 0.95>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Nd_base} object {Nd_letter}
    texture
    {
      pigment {rgb 0.3}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 61 Promethium
#declare Pm_base = sphere {<0, 0, 0>, (atom_min_radius + (((61 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Pm_letter = text {ttf "cyrvetic.ttf" "Pm" 20 0 scale 0.52 translate <-0.5 + 0.16, -0.5 + 0.3, -5>}
#declare Pm_atom = union
{
  difference
  {
    object {Pm_base} object {Pm_letter}
    texture
    {
      pigment {rgb <0.9, 1.1, 0.9>}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Pm_base} object {Pm_letter}
    texture
    {
      pigment {rgb 0.3}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 62 Samarium
#declare Sm_base = sphere {<0, 0, 0>, (atom_min_radius + (((62 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Sm_letter = text {ttf "cyrvetic.ttf" "Sm" 20 0 scale 0.52 translate <-0.5 + 0.13, -0.5 + 0.3, -5>}
#declare Sm_atom = union
{
  difference
  {
    object {Sm_base} object {Sm_letter}
    texture
    {
      pigment {rgb <0.9, 0.9, 0.78>}
      finish {ambient 0.35 reflection 0.3 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Sm_base} object {Sm_letter}
    texture
    {
      pigment {rgb 0.21}
      finish {ambient 0.35 reflection 0.3 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 63 Europium
#declare Eu_base = sphere {<0, 0, 0>, (atom_min_radius + (((63 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Eu_letter = text {ttf "cyrvetic.ttf" "Eu" 20 0 scale 0.6 translate <-0.5 + 0.2, -0.5 + 0.28, -5>}
#declare Eu_atom = union
{
  difference
  {
    object {Eu_base} object {Eu_letter}
    texture
    {
      pigment {rgb <0.85, 0.85, 0.8>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Eu_base} object {Eu_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 64 Gadolinium
#declare Gd_base = sphere {<0, 0, 0>, (atom_min_radius + (((64 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Gd_letter = text {ttf "cyrvetic.ttf" "Gd" 20 0 scale 0.6 translate <-0.5 + 0.12, -0.5 + 0.28, -5>}
#declare Gd_atom = union
{
  difference
  {
    object {Gd_base} object {Gd_letter}
    texture
    {
      pigment {rgb 0.6}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Gd_base} object {Gd_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 65 Terbium
#declare Tb_base = sphere {<0, 0, 0>, (atom_min_radius + (((65 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Tb_letter = text {ttf "cyrvetic.ttf" "Tb" 20 0 scale 0.6 translate <-0.5 + 0.19, -0.5 + 0.27, -5>}
#declare Tb_atom = union
{
  difference
  {
    object {Tb_base} object {Tb_letter}
    texture
    {
      pigment {rgb 0.8}
      finish {ambient 0.35 reflection 0.55 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Tb_base} object {Tb_letter}
    texture
    {
      pigment {rgb 0.25}
      finish {ambient 0.35 reflection 0.55 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 66 Dysprosium
#declare Dy_base = sphere {<0, 0, 0>, (atom_min_radius + (((6 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Dy_letter = text {ttf "cyrvetic.ttf" "Dy" 20 0 scale 0.55 translate <-0.5 + 0.22, -0.5 + 0.3, -5>}
#declare Dy_atom = union
{
  difference
  {
    object {Dy_base} object {Dy_letter}
    texture
    {
      pigment {rgb 0.64}
      finish {ambient 0.35 reflection 0.3 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Dy_base} object {Dy_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35 reflection 0.3 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 67 Holmium
#declare Ho_base = sphere {<0, 0, 0>, (atom_min_radius + (((67 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ho_letter = text {ttf "cyrvetic.ttf" "Ho" 20 (-0.03 * x) scale 0.6 translate <-0.5 + 0.18, -0.5 + 0.27, -5>}
#declare Ho_atom = union
{
  difference
  {
    object {Ho_base} object {Ho_letter}
    texture
    {
      pigment {rgb 0.85}
      finish {ambient 0.35 reflection 0.45 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ho_base} object {Ho_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.45 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 68 Erbium
#declare Er_base = sphere {<0, 0, 0>, (atom_min_radius + (((68 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Er_letter = text {ttf "cyrvetic.ttf" "Er" 20 0 scale 0.7 translate <-0.5 + 0.225, -0.5 + 0.24, -5>}
#declare Er_atom = union
{
  difference
  {
    object {Er_base} object {Er_letter}
    texture
    {
      pigment {rgb 0.85}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Er_base} object {Er_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 69 Thulium
#declare Tm_base = sphere {<0, 0, 0>, (atom_min_radius + (((69 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Tm_letter = text {ttf "cyrvetic.ttf" "Tm" 20 0 scale 0.53 translate <-0.5 + 0.14, -0.5 + 0.3, -5>}
#declare Tm_atom = union
{
  difference
  {
    object {Tm_base} object {Tm_letter}
    texture
    {
      pigment {rgb 0.7}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Tm_base} object {Tm_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 70 Ytterbium
#declare Yb_base = sphere {<0, 0, 0>, (atom_min_radius + (((70 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Yb_letter = text {ttf "cyrvetic.ttf" "Yb" 20 0 scale 0.6 translate <-0.5 + 0.17, -0.5 + 0.27, -5>}
#declare Yb_atom = union
{
  difference
  {
    object {Yb_base} object {Yb_letter}
    texture
    {
      pigment {rgb <0.8, 0.8, 0.72>}
      finish {ambient 0.35 reflection 0.5 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Yb_base} object {Yb_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.5 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 71 Lutetium
#declare Lu_base = sphere {<0, 0, 0>, (atom_min_radius + (((71 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Lu_letter = text {ttf "cyrvetic.ttf" "Lu" 20 0 scale 0.6 translate <-0.5 + 0.22, -0.5 + 0.28, -5>}
#declare Lu_atom = union
{
  difference
  {
    object {Lu_base} object {Lu_letter}
    texture
    {
      pigment {rgb 0.68}
      finish {ambient 0.35 reflection 0.3 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Lu_base} object {Lu_letter}
    texture
    {
      pigment {rgb 0.17}
      finish {ambient 0.35 reflection 0.3 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 72 Hafnium
#declare Hf_base = sphere {<0, 0, 0>, (atom_min_radius + (((72 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Hf_letter = text {ttf "cyrvetic.ttf" "Hf" 20 0 scale 0.65 translate <-0.5 + 0.2, -0.5 + 0.25, -5>}
#declare Hf_atom = union
{
  difference
  {
    object {Hf_base} object {Hf_letter}
    texture
    {
      pigment {rgb 0.65}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.075 metallic}
    }
  }
  intersection
  {
    object {Hf_base} object {Hf_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.075 metallic}
    }
  }
  no_shadow
}

// 73 Tantalum
#declare Ta_base = sphere {<0, 0, 0>, (atom_min_radius + (((73 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ta_letter = text {ttf "cyrvetic.ttf" "Ta" 20 (-0.08 * x) scale 0.6 translate <-0.5 + 0.19, -0.5 + 0.28, -5>}
#declare Ta_atom = union
{
  difference
  {
    object {Ta_base} object {Ta_letter}
    texture
    {
      pigment {rgb <0.75, 0.75, 0.85>}
      finish {ambient 0.35 reflection 0.6 specular 0.4 roughness 0.02 metallic}
    }
  }
  intersection
  {
    object {Ta_base} object {Ta_letter}
    texture
    {
      pigment {rgb <0.75, 0.75, 0.85> * 0.2}
      finish {ambient 0.35 reflection 0.6 specular 0.4 roughness 0.02 metallic}
    }
  }
  no_shadow
}

// 74 Tungsten
#declare W_base = sphere {<0, 0, 0>, (atom_min_radius + (((74 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare W_letter = text {ttf "cyrvetic.ttf" "W" 20 0 scale 0.7 translate <-0.5 + 0.191, -0.5 + 0.22, -5>}
#declare W_atom = union
{
  difference
  {
    object {W_base} object {W_letter}
    texture
    {
      pigment {rgb 0.72}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {W_base} object {W_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 75 Rhenium
#declare Re_base = sphere {<0, 0, 0>, (atom_min_radius + (((75 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Re_letter = text {ttf "cyrvetic.ttf" "Re" 20 0 scale 0.6 translate <-0.5 + 0.2, -0.5 + 0.29, -5>}
#declare Re_atom = union
{
  difference
  {
    object {Re_base} object {Re_letter}
    texture
    {
      pigment {rgb 0.68}
      finish {ambient 0.35 reflection 0.65 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Re_base} object {Re_letter}
    texture
    {
      pigment {rgb 0.15}
      finish {ambient 0.35 reflection 0.65 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 76 Osmium
#declare Os_base = sphere {<0, 0, 0>, (atom_min_radius + (((76 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Os_letter = text {ttf "cyrvetic.ttf" "Os" 20 0 scale 0.6 translate <-0.5 + 0.15, -0.5 + 0.28, -5>}
#declare Os_atom = union
{
  difference
  {
    object {Os_base} object {Os_letter}
    texture
    {
      pigment {rgb <0.7, 0.7, 0.85>}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.075 metallic}
    }
  }
  intersection
  {
    object {Os_base} object {Os_letter}
    texture
    {
      pigment {rgb 0.3}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.075 metallic}
    }
  }
  no_shadow
}

// 77 Iridium
#declare Ir_base = sphere {<0, 0, 0>, (atom_min_radius + (((77 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ir_letter = text {ttf "cyrvetic.ttf" "Ir" 20 0 scale 0.7 translate <-0.5 + 0.37, -0.5 + 0.25, -5>}
#declare Ir_atom = union
{
  difference
  {
    object {Ir_base} object {Ir_letter}
    texture
    {
      pigment {rgb 0.82}
      finish {ambient 0.35 reflection 0.45 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ir_base} object {Ir_letter}
    texture
    {
      pigment {rgb 0.18}
      finish {ambient 0.35 reflection 0.45 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 78 Platinum
#declare Pt_base = sphere {<0, 0, 0>, (atom_min_radius + (((78 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Pt_letter = text {ttf "cyrvetic.ttf" "Pt" 20 0 scale 0.7 translate <-0.5 + 0.21, -0.5 + 0.24, -5>}
#declare Pt_atom = union
{
  difference
  {
    object {Pt_base} object {Pt_letter}
    texture
    {
      pigment {rgb 0.92}
      finish {ambient 0.35 reflection 0.95 specular 0.75 roughness 0.005 metallic}
    }
  }
  intersection
  {
    object {Pt_base} object {Pt_letter}
    texture
    {
      pigment {rgb 0.4}
      finish {ambient 0.35 reflection 0.95 specular 0.75 roughness 0.005 metallic}
    }
  }
  no_shadow
}

// 79 Gold
#declare Au_base = sphere {<0, 0, 0>, (atom_min_radius + (((79 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Au_letter = text {ttf "cyrvetic.ttf" "Au" 20 0 scale 0.6 translate <-0.5 + 0.17, -0.5 + 0.3, -5>}
#declare Au_atom = union
{
  difference
  {
    object {Au_base} object {Au_letter}
    texture
    {
      pigment {rgb <1, 0.78, 0>}
      finish {ambient 0.35 reflection 1 specular 0.75 roughness 0.005 metallic}
    }
  }
  intersection
  {
    object {Au_base} object {Au_letter}
    texture
    {
      pigment {rgb 0.9}
      // pigment {rgb <1, 0.78, 0> * 0.45}
      finish {ambient 0.6 reflection 1 specular 0.75 roughness 0.005 metallic}
    }
  }
  no_shadow
}

// 80 Mercury
#declare Hg_base = sphere {<0, 0, 0>, (atom_min_radius + (((80 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Hg_letter = text {ttf "cyrvetic.ttf" "Hg" 20 0 scale 0.6 translate <-0.5 + 0.16, -0.5 + 0.3, -5>}
#declare Hg_atom = union
{
  difference
  {
    object {Hg_base} object {Hg_letter}
    texture
    {
      pigment {rgb 0.9}
      finish {ambient 0.25 reflection 0.8 specular 0.4 roughness 0.01 metallic}
    }
  }
  intersection
  {
    object {Hg_base} object {Hg_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.25 reflection 0.8 specular 0.4 roughness 0.01 metallic}
    }
  }
  no_shadow
}

// 81 Thallium
#declare Tl_base = sphere {<0, 0, 0>, (atom_min_radius + (((81 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Tl_letter = text {ttf "cyrvetic.ttf" "Tl" 20 0 scale 0.7 translate <-0.5 + 0.2, -0.5 + 0.24, -5>}
#declare Tl_atom = union
{
  difference
  {
    object {Tl_base} object {Tl_letter}
    texture
    {
      pigment {rgb 0.65}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Tl_base} object {Tl_letter}
    texture
    {
      pigment {rgb 0.14}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 82 Lead
#declare Pb_base = sphere {<0, 0, 0>, (atom_min_radius + (((82 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Pb_letter = text {ttf "cyrvetic.ttf" "Pb" 20 0 scale 0.6 translate <-0.5 + 0.21, -0.5 + 0.28, -5>}
#declare Pb_atom = union
{
  difference
  {
    object {Pb_base} object {Pb_letter}
    texture
    {
      pigment {rgb 0.6}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.1 metallic}
    }
  }
  intersection
  {
    object {Pb_base} object {Pb_letter}
    texture
    {
      pigment {rgb 0.1}
      finish {ambient 0.35 reflection 0.1 specular 0.4 roughness 0.1 metallic}
    }
  }
  no_shadow
}

// 83 Bismuth
#declare Bi_base = sphere {<0, 0, 0>, (atom_min_radius + (((83 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Bi_letter = text {ttf "cyrvetic.ttf" "Bi" 20 0 scale 0.7 translate <-0.5 + 0.24, -0.5 + 0.24, -5>}
#declare Bi_atom = union
{
  difference
  {
    object {Bi_base} object {Bi_letter}
    texture
    {
      pigment {rgb <1, 0.8, 0.6>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Bi_base} object {Bi_letter}
    texture
    {
      pigment {rgb <1, 0.8, 0.6> * 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 84 Polonium
#declare Po_base = sphere {<0, 0, 0>, (atom_min_radius + (((84 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Po_letter = text {ttf "cyrvetic.ttf" "Po" 20 0 scale 0.65 translate <-0.5 + 0.2, -0.5 + 0.26, -5>}
#declare Po_atom = union
{
  difference
  {
    object {Po_base} object {Po_letter}
    texture
    {
      pigment {rgb 0.76}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Po_base} object {Po_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.2 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 85 Astatine
#declare At_base = sphere {<0, 0, 0>, (atom_min_radius + (((85 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare At_letter = text {ttf "cyrvetic.ttf" "At" 20 0 scale 0.6 translate <-0.5 + 0.2, -0.5 + 0.29, -5>}
#declare At_atom = union
{
  difference
  {
    object {At_base} object {At_letter}
    texture
    {
      pigment {rgb 0.55}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {At_base} object {At_letter}
    texture
    {
      pigment {rgb 0.15}
      finish {ambient 0.35 reflection 0.25 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 86 Radon
#declare Rn_base = sphere {<0, 0, 0>, (atom_min_radius + (((86 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Rn_letter = text {ttf "cyrvetic.ttf" "Rn" 20 0 scale 0.6 translate <-0.5 + 0.19, -0.5 + 0.28, -5>}
#declare Rn_atom = union
{
  difference
  {
    object {Rn_base} object {Rn_letter}
    texture
    {
      pigment {rgb <0.4, 1, 0.4>}
      finish {ambient 0.35}  // {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Rn_base} object {Rn_letter}
    texture
    {
      pigment {rgb 0.95}
      finish {ambient 0.35}
    }
  }
  no_shadow
}

// 87 Francium
#declare Fr_base = sphere {<0, 0, 0>, (atom_min_radius + (((87 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Fr_letter = text {ttf "cyrvetic.ttf" "Fr" 20 0 scale 0.7 translate <-0.5 + 0.24, -0.5 + 0.25, -5>}
#declare Fr_atom = union
{
  difference
  {
    object {Fr_base} object {Fr_letter}
    texture
    {
      pigment {rgb 0.6}
      finish {ambient 0.35 reflection 0.7 specular 0.4 roughness 0.05 metallic}
    }
  }
  intersection
  {
    object {Fr_base} object {Fr_letter}
    texture
    {
      pigment {rgb 0.08}
      finish {ambient 0.35 reflection 0.7 specular 0.4 roughness 0.05 metallic}
    }
  }
  no_shadow
}

// 88 Radium
#declare Ra_base = sphere {<0, 0, 0>, (atom_min_radius + (((88 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ra_letter = text {ttf "cyrvetic.ttf" "Ra" 20 0 scale 0.6 translate <-0.5 + 0.17, -0.5 + 0.28, -5>}
#declare Ra_atom = union
{
  difference
  {
    object {Ra_base} object {Ra_letter}
    texture
    {
      pigment {rgb 1.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ra_base} object {Ra_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.7 roughness 0.025}
    }
  }
  no_shadow
}

// 89 Actinium
#declare Ac_base = sphere {<0, 0, 0>, (atom_min_radius + (((89 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Ac_letter = text {ttf "cyrvetic.ttf" "Ac" 20 0 scale 0.62 translate <-0.5 + 0.16, -0.5 + 0.3, -5>}
#declare Ac_atom = union
{
  difference
  {
    object {Ac_base} object {Ac_letter}
    texture
    {
      pigment {rgb <0.8, 0.8, 1.1>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Ac_base} object {Ac_letter}
    texture
    {
      pigment {rgb 0.22}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 90 Thorium
#declare Th_base = sphere {<0, 0, 0>, (atom_min_radius + (((90 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Th_letter = text {ttf "cyrvetic.ttf" "Th" 20 0 scale 0.6 translate <-0.5 + 0.18, -0.5 + 0.27, -5>}
#declare Th_atom = union
{
  difference
  {
    object {Th_base} object {Th_letter}
    texture
    {
      pigment {rgb 0.5}
      finish {ambient 0.35 reflection 0.55 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Th_base} object {Th_letter}
    texture
    {
      pigment {rgb 0.05}
      finish {ambient 0.35 reflection 0.55 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 91 Protactinium
#declare Pa_base = sphere {<0, 0, 0>, (atom_min_radius + (((91 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Pa_letter = text {ttf "cyrvetic.ttf" "Pa" 20 0 scale 0.6 translate <-0.5 + 0.2, -0.5 + 0.3, -5>}
#declare Pa_atom = union
{
  difference
  {
    object {Pa_base} object {Pa_letter}
    texture
    {
      pigment {rgb 0.8}
      finish {ambient 0.35 reflection 0.48 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Pa_base} object {Pa_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.48 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 91 Uranium
#declare U_base = sphere {<0, 0, 0>, (atom_min_radius + (((91 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare U_letter = text {ttf "cyrvetic.ttf" "U" 20 0 scale 0.7 translate <-0.5 + 0.309, -0.5 + 0.24, -5>}
#declare U_atom = union
{
  difference
  {
    object {U_base} object {U_letter}
    texture
    {
      pigment {rgb 0.6}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {U_base} object {U_letter}
    texture
    {
      pigment {rgb <0, 0, 0>}
      finish {ambient 0.35 specular 0.3 roughness 0.1}
    }
  }
  no_shadow
}

// 93 Neptunium
#declare Np_base = sphere {<0, 0, 0>, (atom_min_radius + (((93 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Np_letter = text {ttf "cyrvetic.ttf" "Np" 20 0 scale 0.6 translate <-0.5 + 0.18, -0.5 + 0.29, -5>}
#declare Np_atom = union
{
  difference
  {
    object {Np_base} object {Np_letter}
    texture
    {
      pigment {rgb 0.78}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Np_base} object {Np_letter}
    texture
    {
      pigment {rgb 0.16}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 94 Plutonium
#declare Pu_base = sphere {<0, 0, 0>, (atom_min_radius + (((94 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Pu_letter = text {ttf "cyrvetic.ttf" "Pu" 20 0 scale 0.65 translate <-0.5 + 0.17, -0.5 + 0.27, -5>}
#declare Pu_atom = union
{
  difference
  {
    object {Pu_base} object {Pu_letter}
    texture
    {
      pigment {rgb 0.8}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Pu_base} object {Pu_letter}
    texture
    {
      pigment {rgb 0.18}
      finish {ambient 0.35 specular 0.4 roughness 0.05}
    }
  }
  no_shadow
}

// 95 Americium
#declare Am_base = sphere {<0, 0, 0>, (atom_min_radius + (((95 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Am_letter = text {ttf "cyrvetic.ttf" "Am" 20 0 scale 0.52 translate <-0.5 + 0.13, -0.5 + 0.32, -5>}
#declare Am_atom = union
{
  difference
  {
    object {Am_base} object {Am_letter}
    texture
    {
      pigment {rgb 0.82}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.05 metallic}
    }
  }
  intersection
  {
    object {Am_base} object {Am_letter}
    texture
    {
      pigment {rgb 0.3}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.05 metallic}
    }
  }
  no_shadow
}

// 96 Curium
#declare Cm_base = sphere {<0, 0, 0>, (atom_min_radius + (((96 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Cm_letter = text {ttf "cyrvetic.ttf" "Cm" 20 0 scale 0.52 translate <-0.5 + 0.12, -0.5 + 0.32, -5>}
#declare Cm_atom = union
{
  difference
  {
    object {Cm_base} object {Cm_letter}
    texture
    {
      pigment {rgb <0.8, 0.3, 0.8>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Cm_base} object {Cm_letter}
    texture
    {
      pigment {rgb <0.8, 0.3, 0.8> * 0.3}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 97 Berkelium
#declare Bk_base = sphere {<0, 0, 0>, (atom_min_radius + (((97 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Bk_letter = text {ttf "cyrvetic.ttf" "Bk" 20 0 scale 0.6 translate <-0.5 + 0.2, -0.5 + 0.28, -5>}
#declare Bk_atom = union
{
  difference
  {
    object {Bk_base} object {Bk_letter}
    texture
    {
      pigment {rgb 0.79}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Bk_base} object {Bk_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 98 Californium
#declare Cf_base = sphere {<0, 0, 0>, (atom_min_radius + (((98 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Cf_letter = text {ttf "cyrvetic.ttf" "Cf" 20 0 scale 0.65 translate <-0.5 + 0.17, -0.5 + 0.265, -5>}
#declare Cf_atom = union
{
  difference
  {
    object {Cf_base} object {Cf_letter}
    texture
    {
      pigment {rgb 0.84}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Cf_base} object {Cf_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 99 Einsteinium
#declare Es_base = sphere {<0, 0, 0>, (atom_min_radius + (((99 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Es_letter = text {ttf "cyrvetic.ttf" "Es" 20 0 scale 0.65 translate <-0.5 + 0.2, -0.5 + 0.26, -5>}
#declare Es_atom = union
{
  difference
  {
    object {Es_base} object {Es_letter}
    texture
    {
      pigment {rgb <0.3, 0.3, 0.8>}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Es_base} object {Es_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 100 Fermium
#declare Fm_base = sphere {<0, 0, 0>, (atom_min_radius + (((100 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Fm_letter = text {ttf "cyrvetic.ttf" "Fm" 20 0 scale 0.55 translate <-0.5 + 0.15, -0.5 + 0.28, -5>}
#declare Fm_atom = union
{
  difference
  {
    object {Fm_base} object {Fm_letter}
    texture
    {
      pigment {rgb 0.75}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Fm_base} object {Fm_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 101 Mendelevium
#declare Md_base = sphere {<0, 0, 0>, (atom_min_radius + (((101 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Md_letter = text {ttf "cyrvetic.ttf" "Md" 20 0 scale 0.55 translate <-0.5 + 0.16, -0.5 + 0.3, -5>}
#declare Md_atom = union
{
  difference
  {
    object {Md_base} object {Md_letter}
    texture
    {
      pigment {rgb 0.73}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Md_base} object {Md_letter}
    texture
    {
      pigment {rgb 0.21}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 102 Nobelium
#declare No_base = sphere {<0, 0, 0>, (atom_min_radius + (((102 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare No_letter = text {ttf "cyrvetic.ttf" "No" 20 0 scale 0.6 translate <-0.5 + 0.18, -0.5 + 0.28, -5>}
#declare No_atom = union
{
  difference
  {
    object {No_base} object {No_letter}
    texture
    {
      pigment {rgb 0.64}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {No_base} object {No_letter}
    texture
    {
      pigment {rgb 0.16}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 103 Lawrencium
#declare Lr_base = sphere {<0, 0, 0>, (atom_min_radius + (((103 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Lr_letter = text {ttf "cyrvetic.ttf" "Lr" 20 0 scale 0.7 translate <-0.5 + 0.25, -0.5 + 0.24, -5>}
#declare Lr_atom = union
{
  difference
  {
    object {Lr_base} object {Lr_letter}
    texture
    {
      pigment {rgb 0.78}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Lr_base} object {Lr_letter}
    texture
    {
      pigment {rgb 0.32}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 104 Rutherfordium
#declare Rf_base = sphere {<0, 0, 0>, (atom_min_radius + (((104 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Rf_letter = text {ttf "cyrvetic.ttf" "Rf" 20 0 scale 0.7 translate <-0.5 + 0.2, -0.5 + 0.23, -5>}
#declare Rf_atom = union
{
  difference
  {
    object {Rf_base} object {Rf_letter}
    texture
    {
      pigment {rgb 0.67}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Rf_base} object {Rf_letter}
    texture
    {
      pigment {rgb 0.23}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 105 Dubnium
#declare Db_base = sphere {<0, 0, 0>, (atom_min_radius + (((105 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Db_letter = text {ttf "cyrvetic.ttf" "Db" 20 0 scale 0.6 translate <-0.5 + 0.19, -0.5 + 0.28, -5>}
#declare Db_atom = union
{
  difference
  {
    object {Db_base} object {Db_letter}
    texture
    {
      pigment {rgb 0.85}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Db_base} object {Db_letter}
    texture
    {
      pigment {rgb 0.33}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 106 Seaborgium
#declare Sg_base = sphere {<0, 0, 0>, (atom_min_radius + (((106 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Sg_letter = text {ttf "cyrvetic.ttf" "Sg" 20 0 scale 0.6 translate <-0.5 + 0.17, -0.5 + 0.29, -5>}
#declare Sg_atom = union
{
  difference
  {
    object {Sg_base} object {Sg_letter}
    texture
    {
      pigment {rgb 0.83}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Sg_base} object {Sg_letter}
    texture
    {
      pigment {rgb 0.2}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 107 Bohrium
#declare Bh_base = sphere {<0, 0, 0>, (atom_min_radius + (((107 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Bh_letter = text {ttf "cyrvetic.ttf" "Bh" 20 0 scale 0.65 translate <-0.5 + 0.16, -0.5 + 0.26, -5>}
#declare Bh_atom = union
{
  difference
  {
    object {Bh_base} object {Bh_letter}
    texture
    {
      pigment {rgb 0.74}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Bh_base} object {Bh_letter}
    texture
    {
      pigment {rgb 0.18}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 108 Hassium
#declare Hs_base = sphere {<0, 0, 0>, (atom_min_radius + (((108 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Hs_letter = text {ttf "cyrvetic.ttf" "Hs" 20 0 scale 0.6 translate <-0.5 + 0.18, -0.5 + 0.27, -5>}
#declare Hs_atom = union
{
  difference
  {
    object {Hs_base} object {Hs_letter}
    texture
    {
      pigment {rgb 0.85}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Hs_base} object {Hs_letter}
    texture
    {
      pigment {rgb 0.14}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// 109 Meitnerium
#declare Mt_base = sphere {<0, 0, 0>, (atom_min_radius + (((109 - 1) / 108) * (atom_max_radius - atom_min_radius)))}
#declare Mt_letter = text {ttf "cyrvetic.ttf" "Mt" 20 0 scale 0.65 translate <-0.5 + 0.18, -0.5 + 0.26, -5>}
#declare Mt_atom = union
{
  difference
  {
    object {Mt_base} object {Mt_letter}
    texture
    {
      pigment {rgb 0.91}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  intersection
  {
    object {Mt_base} object {Mt_letter}
    texture
    {
      pigment {rgb 0.27}
      finish {ambient 0.35 reflection 0.4 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// ??? Delta
#declare Delta_base = sphere {0, atom_max_radius}
#declare Delta_letter = text {ttf "times.ttf" letter_Delta 20 0 scale 0.8 translate <-0.5 + 0.255, -0.5 + 0.27, -5>}
#declare Delta_atom = union
{
  difference
  {
    object {Delta_base} object {Delta_letter}
    texture
    {
      pigment
      {
        gradient z
        color_map
        {
          [0.0 color rgb <0, 0, 0>]
          [0.3 color rgb <0, 0, 0>]
          [0.5 color rgb <1, 1, 1>]
          [0.7 color rgb <0, 0, 0>]
          [1.0 color rgb <0, 0, 0>]
        }
        translate -0.5 * z
      }
      finish {ambient 0 reflection 1}// diffuse 0}
    }
  }
  intersection
  {
    object {Delta_base} object {Delta_letter}
    texture
    {
      pigment {rgb 1}
      finish {ambient 0 reflection 1 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// ??? Theta
#declare Theta_base = sphere {0, atom_max_radius}
#declare Theta_letter = text {ttf "times.ttf" letter_Theta 20 0 scale 0.8 translate <-0.5 + 0.242, -0.5 + 0.24, -5>}
#declare Theta_atom = union
{
  difference
  {
    object {Theta_base} object {Theta_letter}
    texture
    {
      pigment
      {
        gradient z
        color_map
        {
          [0.0 color rgb <0, 0, 0>]
          [0.3 color rgb <0, 0, 0>]
          [0.5 color rgb <1, 1, 1>]
          [0.7 color rgb <0, 0, 0>]
          [1.0 color rgb <0, 0, 0>]
        }
        translate -0.5 * z
      }
      finish {ambient 0 reflection 1}// diffuse 0}
    }
  }
  intersection
  {
    object {Theta_base} object {Theta_letter}
    texture
    {
      pigment {rgb 1}
      finish {ambient 0 reflection 1 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// ??? Sigma
#declare Sigma_base = sphere {0, atom_max_radius}
#declare Sigma_letter = text {ttf "times.ttf" letter_Sigma 20 0 scale 0.8 translate <-0.5 + 0.25, -0.5 + 0.22, -5>}
#declare Sigma_atom = union
{
  difference
  {
    object {Sigma_base} object {Sigma_letter}
    texture
    {
      pigment
      {
        gradient z
        color_map
        {
          [0.0 color rgb <0, 0, 0>]
          [0.3 color rgb <0, 0, 0>]
          [0.5 color rgb <1, 1, 1>]
          [0.7 color rgb <0, 0, 0>]
          [1.0 color rgb <0, 0, 0>]
        }
        translate -0.5 * z
      }
      finish {ambient 0 reflection 1}// diffuse 0}
    }
  }
  intersection
  {
    object {Sigma_base} object {Sigma_letter}
    texture
    {
      pigment {rgb 1}
      finish {ambient 0 reflection 1 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}

// ??? Omega
#declare Omega_base = sphere {0, atom_max_radius}
#declare Omega_letter = text {ttf "times.ttf" letter_Omega_large 20 0 scale 0.8 translate <-0.5 + 0.224, -0.5 + 0.22, -5>}
#declare Omega_atom = union
{
  difference
  {
    object {Omega_base} object {Omega_letter}
    texture
    {
      pigment
      {
        gradient z
        color_map
        {
          [0.0 color rgb <0, 0, 0>]
          [0.3 color rgb <0, 0, 0>]
          [0.5 color rgb <1, 1, 1>]
          [0.7 color rgb <0, 0, 0>]
          [1.0 color rgb <0, 0, 0>]
        }
        translate -0.5 * z
      }
      finish {ambient 0 reflection 1}// diffuse 0}
    }
  }
  intersection
  {
    object {Omega_base} object {Omega_letter}
    texture
    {
      pigment {rgb 1}
      finish {ambient 0 reflection 1 specular 0.4 roughness 0.025 metallic}
    }
  }
  no_shadow
}


// reactor parts

#declare straight_track = union
{
  cylinder {<-0.5, 0, 0>, <0.5, 0, 0>, 0.04}
  sphere {<-0.5, 0, 0>, 0.04}
  sphere {<0.5, 0, 0>, 0.04}
  no_shadow
}

#declare straight_red = object {straight_track texture {red_tex}}
#declare straight_blue = object {straight_track texture {blue_tex}}

#declare curved_track = union
{
  difference
  {
    torus {(1/3), 0.04 rotate 90 * x}
    plane {-y, 0}
    plane {-x, 0}
    translate <-(1/6), -(1/6), 0>
  }
  sphere {<-0.5, -(1/6), 0>, 0.04}
  sphere {<-0.5, 0, 0>, 0.04}
  sphere {<-(1/6), -0.5, 0>, 0.04}
  sphere {<0, -0.5, 0>, 0.04}
  cylinder {<-0.5, -(1/6), 0>, <-0.5, 0, 0>, 0.04}
  cylinder {<-(1/6), -0.5, 0>, <0, -0.5, 0>, 0.04}
  translate <0.5, 0.5, 0>
  no_shadow
}

#declare curved_red = object {curved_track texture {red_tex}}
#declare curved_blue = object {curved_track texture {blue_tex}}

#declare red_ud = object {straight_red rotate 90 * z translate <(1/3), (2/3), red_layer>}
#declare red_lr = object {straight_red translate <(1/3), (2/3), red_layer>}
#declare red_ur = object {curved_red translate <(1/3), (2/3), red_layer>}
#declare red_ul = object {curved_red rotate 90 * z translate <(1/3), (2/3), red_layer>}
#declare red_dr = object {curved_red rotate -90 * z translate <(1/3), (2/3), red_layer>}
#declare red_dl = object {curved_red rotate 180 * z translate <(1/3), (2/3), red_layer>}

#declare blue_ud = object {straight_blue rotate 90 * z translate <(2/3), (1/3), blue_layer>}
#declare blue_lr = object {straight_blue translate <(2/3), (1/3), blue_layer>}
#declare blue_ur = object {curved_blue translate <(2/3), (1/3), blue_layer>}
#declare blue_ul = object {curved_blue rotate 90 * z translate <(2/3), (1/3), blue_layer>}
#declare blue_dr = object {curved_blue rotate -90 * z translate <(2/3), (1/3), blue_layer>}
#declare blue_dl = object {curved_blue rotate 180 * z translate <(2/3), (1/3), blue_layer>}

#declare loopback_track = union
{
  difference
  {
    torus {0.08, 0.04 rotate 90 * x}
    difference
    {
      box {<-1, -1, -1>, <1, 1, 1>}
      plane {x, 0 rotate 60 * z}
      plane {x, 0 rotate -60 * z}
    }
  }
  sphere {<0.08, 0, 0>, 0.04 rotate 30 * z}
  sphere {<0.08, 0, 0>, 0.04 rotate -30 * z}
  difference
  {
    torus {0.08, 0.04 rotate 90 * x}
    plane {-x, 0}
    plane {-y, 0 rotate 30 * z}
    translate <sqrt(3) * 0.08, 0.08, 0>
  }
  difference
  {
    torus {0.08, 0.04 rotate 90 * x}
    plane {-x, 0}
    plane {y, 0 rotate -30 * z}
    translate <sqrt(3) * 0.08, -0.08, 0>
  }
  sphere {<sqrt(3) * 0.08, 0, 0>, 0.04}
  cylinder {<sqrt(3) * 0.08, 0, 0>, <0.5, 0. 0>, 0.04}
  sphere {<0.5, 0, 0>, 0.04}
  no_shadow
}

#declare red_loopback_r = object {loopback_track translate <(1/3), (2/3), red_layer> texture {red_tex}}
#declare red_loopback_u = object {loopback_track rotate 90 * z translate <(1/3), (2/3), red_layer> texture {red_tex}}
#declare red_loopback_l = object {loopback_track rotate 180 * z translate <(1/3), (2/3), red_layer> texture {red_tex}}
#declare red_loopback_d = object {loopback_track rotate -90 * z translate <(1/3), (2/3), red_layer> texture {red_tex}}

#declare blue_loopback_r = object {loopback_track translate <(2/3), (1/3), blue_layer> texture {blue_tex}}
#declare blue_loopback_u = object {loopback_track rotate 90 * z translate <(2/3), (1/3), blue_layer> texture {blue_tex}}
#declare blue_loopback_l = object {loopback_track rotate 180 * z translate <(2/3), (1/3), blue_layer> texture {blue_tex}}
#declare blue_loopback_d = object {loopback_track rotate -90 * z translate <(2/3), (1/3), blue_layer> texture {blue_tex}}


// reactor controls

//directional controls
#declare directional_cone = cone {<0.11, 0, 0>, 0.11, 0, 0 scale <1, 1, 0.5> no_shadow}
#declare red_cone = object {directional_cone texture {red_tex}}
#declare blue_cone = object {directional_cone texture {blue_tex}}

#declare red_dir_l = object {red_cone translate <0, (2/3), red_control_layer + 0.2>}
#declare red_dir_r = object {red_cone rotate 180 * z translate <1, (2/3), red_control_layer + 0.2>}
#declare red_dir_u = object {red_cone rotate -90 * z translate <(1/3), 1, red_control_layer + 0.2>}
#declare red_dir_d = object {red_cone rotate 90 * z translate <(1/3), 0, red_control_layer + 0.2>}

#declare blue_dir_l = object {blue_cone translate <0, (1/3), blue_control_layer + 0.2>}
#declare blue_dir_r = object {blue_cone rotate 180 * z translate <1, (1/3), blue_control_layer + 0.2>}
#declare blue_dir_u = object {blue_cone rotate -90 * z translate <(2/3), 1, blue_control_layer + 0.2>}
#declare blue_dir_d = object {blue_cone rotate 90 * z translate <(2/3), 0, blue_control_layer + 0.2>}

// start spots
#declare start_word_stick = text {ttf "cyrvetic.ttf" "START" 10 0 scale <0.6, 0.6, 1> translate <-1 + 0.12, -0.5 + 0.28, -5> no_shadow}
#declare red_start = union
{
  difference
  {
    sphere {0, 1}
    object {start_word_stick}
    texture {red_tex}
  }
  intersection
  {
    sphere {0, 1}
    object {start_word_stick}
    texture {white_tex}
  }
  no_shadow
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
}
#declare blue_start = union
{
  difference
  {
    sphere {0, 1}
    object {start_word_stick}
    texture {blue_tex}
  }
  intersection
  {
    sphere {0, 1}
    object {start_word_stick}
    texture {white_tex}
  }
  no_shadow
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
}

#declare red_start_u = union
{
  object {red_start}
  object {directional_cone rotate -90 * z translate <(1/3), (2/3) + 0.3, red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
  object {straight_track translate 0.5 * x scale <0.5, 1, 1> rotate 90 * z translate <(1/3), (2/3), red_layer> texture {red_tex}}
}
#declare red_start_d = union
{
  object {red_start}
  object {directional_cone rotate 90 * z translate <(1/3), (2/3) - 0.3, red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
  object {straight_track translate 0.5 * x scale <0.5, 1, 1> rotate -90 * z translate <(1/3), (2/3), red_layer> texture {red_tex}}
}
#declare red_start_l = union
{
  object {red_start}
  object {directional_cone translate <(1/3) - 0.3, (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
  object {straight_track translate 0.5 * x scale <0.5, 1, 1> rotate 180 * z translate <(1/3), (2/3), red_layer> texture {red_tex}}
}
#declare red_start_r = union
{
  object {red_start}
  object {directional_cone rotate 180 * z translate<(1/3) + 0.3, (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
  object {straight_track translate 0.5 * x scale <0.5, 1, 1> translate <(1/3), (2/3), red_layer> texture {red_tex}}
}

#declare blue_start_u = union
{
  object {blue_start}
  object {directional_cone rotate -90 * z translate <(2/3), (1/3) + 0.3, blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
  object {straight_track translate 0.5 * x scale <0.5, 1, 1> rotate 90 * z translate <(2/3), (1/3), blue_layer> texture {blue_tex}}
}
#declare blue_start_d = union
{
  object {blue_start}
  object {directional_cone rotate 90 * z translate <(2/3), (1/3) - 0.3, blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
  object {straight_track translate 0.5 * x scale <0.5, 1, 1> rotate -90 * z translate <(2/3), (1/3), blue_layer> texture {blue_tex}}
}
#declare blue_start_l = union
{
  object {blue_start}
  object {directional_cone translate <(2/3) - 0.3, (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
  object {straight_track translate 0.5 * x scale <0.5, 1, 1> rotate 180 * z translate <(2/3), (1/3), blue_layer> texture {blue_tex}}
}
#declare blue_start_r = union
{
  object {blue_start}
  object {directional_cone rotate 180 * z translate<(2/3) + 0.3, (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
  object {straight_track translate 0.5 * x scale <0.5, 1, 1> translate <(2/3), (1/3), blue_layer> texture {blue_tex}}
}

// bond +/-
#declare bond_minus_word_stick = union
{
  text {ttf "cyrvetic.ttf" "BOND" 10 0 scale <0.65, 0.65, 1> translate <-1 + 0.15, 0, -5>}
  box {<-0.05, -0.4, -5>, <0.05, 0.4, 5> rotate 90 * z translate -0.5 * y}
}

#declare bond_plus_word_stick = union
{
  object {bond_minus_word_stick}
  box {<-0.05, -0.4, -5>, <0.05, 0.4, 5> translate -0.5 * y}
}

#declare red_bond_plus = union
{
  difference {sphere {0, 1} bond_plus_word_stick texture {red_tex}}
  intersection {sphere {0, 1} bond_plus_word_stick texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare red_bond_minus = union
{
  difference {sphere {0, 1} bond_minus_word_stick texture {red_tex}}
  intersection {sphere {0, 1} bond_minus_word_stick texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_bond_plus = union
{
  difference {sphere {0, 1} bond_plus_word_stick texture {blue_tex}}
  intersection {sphere {0, 1} bond_plus_word_stick texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare blue_bond_minus = union
{
  difference {sphere {0, 1} bond_minus_word_stick texture {blue_tex}}
  intersection {sphere {0, 1} bond_minus_word_stick texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// grab/drop
#declare grabdrop_word_stick = union
{
  text {ttf "cyrvetic.ttf" "GRAB" 10 0 scale <0.65, 0.65, 1> translate <-1 + 0.15, 0.05, -5>}
  text {ttf "cyrvetic.ttf" "DROP" 10 0 scale <0.65, 0.65, 1> translate <-1 + 0.2, -1 + 0.45, -5>}
}

#declare red_grabdrop = union
{
  difference {sphere {0, 1} object {grabdrop_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {grabdrop_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare red_grab_drop = red_grabdrop

#declare blue_grabdrop = union
{
  difference {sphere {0, 1} object {grabdrop_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {grabdrop_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}
#declare blue_grab_drop = blue_grabdrop

#declare grab_word_stick = text {ttf "cyrvetic.ttf" "GRAB" 10 0 scale <0.75, 0.75, 1> translate <-1, -0.5 + 0.25, -5> scale <0.95, 0.95, 1>}

#declare red_grab = union
{
  difference {sphere {0, 1} object {grab_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {grab_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_grab = union
{
  difference {sphere {0, 1} object {grab_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {grab_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare drop_word_stick = text {ttf "cyrvetic.ttf" "DROP" 10 0 scale <0.75, 0.75, 1> translate <-1+ 0.025, -0.5 + 0.25, -5> scale <0.95, 0.95, 1>}

#declare red_drop = union
{
  difference {sphere {0, 1} object {drop_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {drop_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_drop = union
{
  difference {sphere {0, 1} object {drop_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {drop_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// in
#declare in_alpha_word_stick = union
{
  text {ttf "cyrvetic.ttf" "IN" 10 0 scale <1, 1, 1> translate <-1 + 0.59, 0.1, -5>}
  text {ttf "times.ttf" letter_alpha 10 0 scale <1.5, 1.5, 1> translate <-1 + 0.65, -1 + 0.25, -5>}
}

#declare red_in_alpha = union
{
  difference {sphere {0, 1} object {in_alpha_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {in_alpha_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_in_alpha = union
{
  difference {sphere {0, 1} object {in_alpha_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {in_alpha_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare in_beta_word_stick = union
{
  text {ttf "cyrvetic.ttf" "IN" 10 0 scale <1, 1, 1> translate <-1 + 0.59, 0.1, -5>}
  text {ttf "times.ttf" letter_beta 10 0 scale <1.1, 1.1, 1> translate <-1 + 0.82, -1 + 0.3, -5>}
}

#declare red_in_beta = union
{
  difference {sphere {0, 1} object {in_beta_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {in_beta_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_in_beta = union
{
  difference {sphere {0, 1} object {in_beta_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {in_beta_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// out
#declare out_psi_word_stick = union
{
  text {ttf "cyrvetic.ttf" "OUT" 10 0 scale <0.75, 0.75, 1> translate <-1 + 0.215, 0.1, -5>}
  text {ttf "times.ttf" letter_psi 10 0 scale <1.3, 1.3, 1> translate <-1 + 0.612, -1 + 0.35, -5>}
}

#declare red_out_psi = union
{
  difference {sphere {0, 1} object {out_psi_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {out_psi_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_out_psi = union
{
  difference {sphere {0, 1} object {out_psi_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {out_psi_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare out_omega_word_stick = union
{
  text {ttf "cyrvetic.ttf" "OUT" 10 0 scale <0.75, 0.75, 1> translate <-1 + 0.215, 0.1, -5>}
  text {ttf "times.ttf" letter_omega_small 10 0 scale <1.75, 1.75, 1> translate <-1 + 0.488, -1 + 0.15, -5>}
}

#declare red_out_omega = union
{
  difference {sphere {0, 1} object {out_omega_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {out_omega_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_out_omega = union
{
  difference {sphere {0, 1} object {out_omega_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {out_omega_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// sync
#declare sync_word_stick = text {ttf "cyrvetic.ttf" "SYNC" 10 0 scale <0.7, 0.7, 1> translate <-1 + 0.08, -0.5 + 0.25, -5>}

#declare red_sync = union
{
  difference {sphere {0, 1} object {sync_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {sync_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_sync = union
{
  difference {sphere {0, 1} object {sync_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {sync_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// rotate
#declare rotate_stick = union
{
  difference
  {
    cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}
    cylinder {<0, 0, -10>, <0, 0, 10>, 0.45}
    box {<0, -1, -10>, <1, 0, 10> rotate 1*z}
    box {<0, -1, -10>, <1, 0, 10> rotate 30*z}
  }
  prism
  {
    linear_spline linear_sweep 10, -10, 4, <0, 0.35>, <0.35, 0>, <0, -0.35>, <0, 0.35>
    rotate 90 * x
    translate <0, -0.6, 0>
  }
}

#declare red_rotate_counterclockwise = union
{
  difference {sphere {0, 1} object {rotate_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {rotate_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_rotate_counterclockwise = union
{
  difference {sphere {0, 1} object {rotate_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {rotate_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_rotate_clockwise = union
{
  difference {sphere {0, 1} object {rotate_stick rotate 180 * y} texture {red_tex}}
  intersection {sphere {0, 1} object {rotate_stick rotate 180 * y} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_rotate_clockwise = union
{
  difference {sphere {0, 1} object {rotate_stick rotate 180 * y} texture {blue_tex}}
  intersection {sphere {0, 1} object {rotate_stick rotate 180 * y} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// Atom sensors -- 2 colors for each of 113 elements
// direction indicator will be added separately

// indicators first
#declare red_indicator_l = object {directional_cone translate <(1/3) - 0.3, (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex} no_shadow}
#declare red_indicator_r = object {directional_cone rotate 180 * z translate <(1/3) + 0.3, (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex} no_shadow}
#declare red_indicator_u = object {directional_cone rotate -90 * z translate <(1/3), (2/3) + 0.3, red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex} no_shadow}
#declare red_indicator_d = object {directional_cone rotate 90 * z translate <(1/3), (2/3) - 0.3, red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex} no_shadow}

#declare blue_indicator_l = object {directional_cone translate <(2/3) - 0.3, (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex} no_shadow}
#declare blue_indicator_r = object {directional_cone rotate 180 * z translate <(2/3) + 0.3, (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex} no_shadow}
#declare blue_indicator_u = object {directional_cone rotate -90 * z translate <(2/3), (1/3) + 0.3, blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex} no_shadow}
#declare blue_indicator_d = object {directional_cone rotate 90 * z translate <(2/3), (1/3) - 0.3, blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex} no_shadow}

// automatically expanding and contracting directional indicators -- for flip-flops and atom sensors
#declare red_indicator_expand_l = object {directional_cone translate <-0.3, 0, 0> scale ((cubic_expand > 0) ? cubic_expand : 0.0001) translate <(1/3), (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare red_indicator_expand_r = object {directional_cone rotate 180 * z translate <0.3, 0, 0> scale ((cubic_expand > 0) ? cubic_expand : 0.0001) translate <(1/3), (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare red_indicator_expand_u = object {directional_cone rotate -90 * z translate <0, 0.3, 0> scale ((cubic_expand > 0) ? cubic_expand : 0.0001) translate <(1/3), (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare red_indicator_expand_d = object {directional_cone rotate 90 * z translate <0, -0.3, 0> scale ((cubic_expand > 0) ? cubic_expand : 0.0001) translate <(1/3), (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare red_indicator_contract_l = object {directional_cone translate <-0.3, 0, 0> scale ((cubic_contract > 0) ? cubic_contract : 0.0001) translate <(1/3), (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare red_indicator_contract_r = object {directional_cone rotate 180 * z translate <0.3, 0, 0> scale ((cubic_contract > 0) ? cubic_contract : 0.0001) translate <(1/3), (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare red_indicator_contract_u = object {directional_cone rotate -90 * z translate <0, 0.3, 0> scale ((cubic_contract > 0) ? cubic_contract : 0.0001) translate <(1/3), (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare red_indicator_contract_d = object {directional_cone rotate 90 * z translate <0, -0.3, 0> scale ((cubic_contract > 0) ? cubic_contract : 0.0001) translate <(1/3), (2/3), red_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}

#declare blue_indicator_expand_l = object {directional_cone translate <-0.3, 0, 0> scale ((cubic_expand > 0) ? cubic_expand : 0.0001) translate <(2/3), (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare blue_indicator_expand_r = object {directional_cone rotate 180 * z translate <0.3, 0, 0> scale ((cubic_expand > 0) ? cubic_expand : 0.0001) translate <(2/3), (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare blue_indicator_expand_u = object {directional_cone rotate -90 * z translate <0, 0.3, 0> scale ((cubic_expand > 0) ? cubic_expand : 0.0001) translate <(2/3), (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare blue_indicator_expand_d = object {directional_cone rotate 90 * z translate <0, -0.3, 0> scale ((cubic_expand > 0) ? cubic_expand : 0.0001) translate <(2/3), (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare blue_indicator_contract_l = object {directional_cone translate <-0.3, 0, 0> scale ((cubic_contract > 0) ? cubic_contract : 0.0001) translate <(2/3), (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare blue_indicator_contract_r = object {directional_cone rotate 180 * z translate <0.3, 0, 0> scale ((cubic_contract > 0) ? cubic_contract : 0.0001) translate <(2/3), (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare blue_indicator_contract_u = object {directional_cone rotate -90 * z translate <0, 0.3, 0> scale ((cubic_contract > 0) ? cubic_contract : 0.0001) translate <(2/3), (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}
#declare blue_indicator_contract_d = object {directional_cone rotate 90 * z translate <0, -0.3, 0> scale ((cubic_contract > 0) ? cubic_contract : 0.0001) translate <(2/3), (1/3), blue_control_layer + 0.1> texture {/*gray_tex*/ silvery_tex}}

// half-track pieces for flip-flops and atom sensors
#declare red_halftrack_r = object {straight_red translate <0.5, 0, 0> scale <0.5, 1, 1> translate <(1/3), (2/3), red_layer>}
#declare red_halftrack_l = object {straight_red translate <-0.5, 0, 0> scale <0.5, 1, 1> translate <(1/3), (2/3), red_layer>}
#declare red_halftrack_u = object {straight_red translate <0.5, 0, 0> scale <0.5, 1, 1> rotate 90 * z translate <(1/3), (2/3), red_layer>}
#declare red_halftrack_d = object {straight_red translate <0.5, 0, 0> scale <0.5, 1, 1> rotate -90 * z translate <(1/3), (2/3), red_layer>}

#declare blue_halftrack_r = object {straight_blue translate <0.5, 0, 0> scale <0.5, 1, 1> translate <(2/3), (1/3), blue_layer>}
#declare blue_halftrack_l = object {straight_blue translate <-0.5, 0, 0> scale <0.5, 1, 1> translate <(2/3), (1/3), blue_layer>}
#declare blue_halftrack_u = object {straight_blue translate <0.5, 0, 0> scale <0.5, 1, 1> rotate 90 * z translate <(2/3), (1/3), blue_layer>}
#declare blue_halftrack_d = object {straight_blue translate <0.5, 0, 0> scale <0.5, 1, 1> rotate -90 * z translate <(2/3), (1/3), blue_layer>}


// 2 sensors each for 113 atoms
#declare H_sensor_letter = object {H_letter scale (0.75/(atom_min_radius + (((1 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_H_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {H_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {H_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_H_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {H_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {H_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare He_sensor_letter = object {He_letter scale (0.75/(atom_min_radius + (((2 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_He_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {He_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {He_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_He_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {He_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {He_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Li_sensor_letter = object {Li_letter scale (0.75/(atom_min_radius + (((3 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Li_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Li_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Li_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Li_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Li_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Li_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Be_sensor_letter = object {Be_letter scale (0.75/(atom_min_radius + (((4 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Be_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Be_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Be_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Be_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Be_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Be_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare B_sensor_letter = object {B_letter scale (0.75/(atom_min_radius + (((5 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_B_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {B_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {B_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_B_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {B_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {B_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare C_sensor_letter = object {C_letter scale (0.75/(atom_min_radius + (((6 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_C_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {C_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {C_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_C_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {C_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {C_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare N_sensor_letter = object {N_letter scale (0.75/(atom_min_radius + (((7 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_N_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {N_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {N_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_N_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {N_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {N_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare O_sensor_letter = object {O_letter scale (0.75/(atom_min_radius + (((8 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_O_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {O_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {O_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_O_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {O_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {O_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare F_sensor_letter = object {F_letter scale (0.75/(atom_min_radius + (((9 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_F_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {F_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {F_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_F_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {F_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {F_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ne_sensor_letter = object {Ne_letter scale (0.75/(atom_min_radius + (((10 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ne_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ne_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ne_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ne_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ne_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ne_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Na_sensor_letter = object {Na_letter scale (0.75/(atom_min_radius + (((11 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Na_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Na_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Na_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Na_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Na_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Na_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Mg_sensor_letter = object {Mg_letter scale (0.75/(atom_min_radius + (((12 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Mg_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mg_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Mg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Mg_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mg_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Mg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Al_sensor_letter = object {Al_letter scale (0.75/(atom_min_radius + (((13 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Al_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Al_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Al_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Al_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Al_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Al_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Si_sensor_letter = object {Si_letter scale (0.75/(atom_min_radius + (((14 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Si_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Si_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Si_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Si_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Si_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Si_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare P_sensor_letter = object {P_letter scale (0.75/(atom_min_radius + (((15 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_P_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {P_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {P_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_P_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {P_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {P_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare S_sensor_letter = object {S_letter scale (0.75/(atom_min_radius + (((16 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_S_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {S_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {S_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_S_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {S_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {S_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Cl_sensor_letter = object {Cl_letter scale (0.75/(atom_min_radius + (((17 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Cl_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cl_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cl_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cl_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cl_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cl_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ar_sensor_letter = object {Ar_letter scale (0.75/(atom_min_radius + (((18 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ar_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ar_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ar_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ar_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ar_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ar_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare K_sensor_letter = object {K_letter scale (0.75/(atom_min_radius + (((19 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_K_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {K_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {K_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_K_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {K_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {K_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ca_sensor_letter = object {Ca_letter scale (0.75/(atom_min_radius + (((20 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ca_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ca_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ca_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ca_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ca_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ca_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Sc_sensor_letter = object {Sc_letter scale (0.75/(atom_min_radius + (((21 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Sc_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sc_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sc_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sc_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sc_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sc_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ti_sensor_letter = object {Ti_letter scale (0.75/(atom_min_radius + (((22 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ti_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ti_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ti_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ti_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ti_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ti_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare V_sensor_letter = object {V_letter scale (0.75/(atom_min_radius + (((23 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_V_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {V_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {V_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_V_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {V_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {V_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Cr_sensor_letter = object {Cr_letter scale (0.75/(atom_min_radius + (((24 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Cr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Mn_sensor_letter = object {Mn_letter scale (0.75/(atom_min_radius + (((25 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Mn_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mn_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Mn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Mn_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mn_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Mn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Fe_sensor_letter = object {Fe_letter scale (0.75/(atom_min_radius + (((26 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Fe_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fe_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Fe_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Fe_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fe_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Fe_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Co_sensor_letter = object {Co_letter scale (0.75/(atom_min_radius + (((27 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Co_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Co_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Co_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Co_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Co_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Co_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ni_sensor_letter = object {Ni_letter scale (0.75/(atom_min_radius + (((28 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ni_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ni_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ni_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ni_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ni_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ni_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Cu_sensor_letter = object {Cu_letter scale (0.75/(atom_min_radius + (((29 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Cu_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cu_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cu_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cu_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Zn_sensor_letter = object {Zn_letter scale (0.75/(atom_min_radius + (((30 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Zn_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Zn_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Zn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Zn_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Zn_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Zn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ga_sensor_letter = object {Ga_letter scale (0.75/(atom_min_radius + (((31 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ga_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ga_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ga_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ga_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ga_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ga_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ge_sensor_letter = object {Ge_letter scale (0.75/(atom_min_radius + (((32 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ge_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ge_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ge_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ge_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ge_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ge_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare As_sensor_letter = object {As_letter scale (0.75/(atom_min_radius + (((33 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_As_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {As_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {As_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_As_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {As_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {As_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Se_sensor_letter = object {Se_letter scale (0.75/(atom_min_radius + (((34 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Se_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Se_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Se_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Se_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Se_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Se_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Br_sensor_letter = object {Br_letter scale (0.75/(atom_min_radius + (((35 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Br_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Br_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Br_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Br_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Br_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Br_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Kr_sensor_letter = object {Kr_letter scale (0.75/(atom_min_radius + (((36 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Kr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Kr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Kr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Kr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Kr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Kr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Rb_sensor_letter = object {Rb_letter scale (0.75/(atom_min_radius + (((37 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Rb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Rb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Rb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Rb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Sr_sensor_letter = object {Sr_letter scale (0.75/(atom_min_radius + (((38 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Sr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Y_sensor_letter = object {Y_letter scale (0.75/(atom_min_radius + (((39 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Y_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Y_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Y_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Y_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Y_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Y_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Zr_sensor_letter = object {Zr_letter scale (0.75/(atom_min_radius + (((40 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Zr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Zr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Zr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Zr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Zr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Zr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Nb_sensor_letter = object {Nb_letter scale (0.75/(atom_min_radius + (((41 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Nb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Nb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Nb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Nb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Nb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Nb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Mo_sensor_letter = object {Mo_letter scale (0.75/(atom_min_radius + (((42 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Mo_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mo_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Mo_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Mo_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mo_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Mo_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Tc_sensor_letter = object {Tc_letter scale (0.75/(atom_min_radius + (((43 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Tc_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tc_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Tc_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Tc_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tc_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Tc_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ru_sensor_letter = object {Ru_letter scale (0.75/(atom_min_radius + (((44 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ru_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ru_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ru_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ru_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ru_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ru_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Rh_sensor_letter = object {Rh_letter scale (0.75/(atom_min_radius + (((45 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Rh_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rh_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Rh_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Rh_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rh_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Rh_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Pd_sensor_letter = object {Pd_letter scale (0.75/(atom_min_radius + (((46 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Pd_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pd_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pd_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pd_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ag_sensor_letter = object {Ag_letter scale (0.75/(atom_min_radius + (((47 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ag_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ag_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ag_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ag_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ag_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ag_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Cd_sensor_letter = object {Cd_letter scale (0.75/(atom_min_radius + (((48 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Cd_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cd_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cd_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cd_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare In_sensor_letter = object {In_letter scale (0.75/(atom_min_radius + (((49 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_In_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {In_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {In_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_In_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {In_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {In_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Sn_sensor_letter = object {Sn_letter scale (0.75/(atom_min_radius + (((50 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Sn_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sn_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sn_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sn_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Sb_sensor_letter = object {Sb_letter scale (0.75/(atom_min_radius + (((51 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Sb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Te_sensor_letter = object {Te_letter scale (0.75/(atom_min_radius + (((52 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Te_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Te_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Te_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Te_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Te_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Te_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare I_sensor_letter = object {I_letter scale (0.75/(atom_min_radius + (((53 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_I_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {I_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {I_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_I_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {I_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {I_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Xe_sensor_letter = object {Xe_letter scale (0.75/(atom_min_radius + (((54 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Xe_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Xe_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Xe_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Xe_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Xe_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Xe_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Cs_sensor_letter = object {Cs_letter scale (0.75/(atom_min_radius + (((55 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Cs_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cs_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cs_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cs_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cs_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cs_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ba_sensor_letter = object {Ba_letter scale (0.75/(atom_min_radius + (((56 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ba_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ba_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ba_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ba_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ba_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ba_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare La_sensor_letter = object {La_letter scale (0.75/(atom_min_radius + (((57 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_La_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {La_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {La_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_La_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {La_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {La_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ce_sensor_letter = object {Ce_letter scale (0.75/(atom_min_radius + (((58 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ce_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ce_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ce_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ce_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ce_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ce_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Pr_sensor_letter = object {Pr_letter scale (0.75/(atom_min_radius + (((59 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Pr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Nd_sensor_letter = object {Nd_letter scale (0.75/(atom_min_radius + (((60 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Nd_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Nd_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Nd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Nd_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Nd_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Nd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Pm_sensor_letter = object {Pm_letter scale (0.75/(atom_min_radius + (((61 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Pm_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pm_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pm_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pm_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Sm_sensor_letter = object {Sm_letter scale (0.75/(atom_min_radius + (((62 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Sm_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sm_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sm_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sm_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Eu_sensor_letter = object {Eu_letter scale (0.75/(atom_min_radius + (((63 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Eu_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Eu_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Eu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Eu_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Eu_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Eu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Gd_sensor_letter = object {Gd_letter scale (0.75/(atom_min_radius + (((64 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Gd_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Gd_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Gd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Gd_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Gd_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Gd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Tb_sensor_letter = object {Tb_letter scale (0.75/(atom_min_radius + (((65 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Tb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Tb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Tb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Tb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Dy_sensor_letter = object {Dy_letter scale (0.75/(atom_min_radius + (((66 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Dy_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Dy_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Dy_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Dy_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Dy_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Dy_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ho_sensor_letter = object {Ho_letter scale (0.75/(atom_min_radius + (((67 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ho_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ho_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ho_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ho_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ho_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ho_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Er_sensor_letter = object {Er_letter scale (0.75/(atom_min_radius + (((68 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Er_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Er_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Er_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Er_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Er_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Er_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Tm_sensor_letter = object {Tm_letter scale (0.75/(atom_min_radius + (((69 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Tm_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tm_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Tm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Tm_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tm_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Tm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Yb_sensor_letter = object {Yb_letter scale (0.75/(atom_min_radius + (((70 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Yb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Yb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Yb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Yb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Yb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Yb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Lu_sensor_letter = object {Lu_letter scale (0.75/(atom_min_radius + (((71 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Lu_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Lu_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Lu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Lu_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Lu_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Lu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Hf_sensor_letter = object {Hf_letter scale (0.75/(atom_min_radius + (((72 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Hf_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hf_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Hf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Hf_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hf_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Hf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ta_sensor_letter = object {Ta_letter scale (0.75/(atom_min_radius + (((73 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ta_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ta_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ta_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ta_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare W_sensor_letter = object {W_letter scale (0.75/(atom_min_radius + (((74 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_W_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {W_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {W_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_W_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {W_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {W_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Re_sensor_letter = object {Re_letter scale (0.75/(atom_min_radius + (((75 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Re_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Re_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Re_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Re_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Re_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Re_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Os_sensor_letter = object {Os_letter scale (0.75/(atom_min_radius + (((76 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Os_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Os_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Os_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Os_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Os_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Os_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ir_sensor_letter = object {Ir_letter scale (0.75/(atom_min_radius + (((77 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ir_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ir_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ir_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ir_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ir_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ir_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Pt_sensor_letter = object {Pt_letter scale (0.75/(atom_min_radius + (((78 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Pt_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pt_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pt_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pt_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pt_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pt_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Au_sensor_letter = object {Au_letter scale (0.75/(atom_min_radius + (((79 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Au_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Au_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Au_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Au_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Au_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Au_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Hg_sensor_letter = object {Hg_letter scale (0.75/(atom_min_radius + (((80 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Hg_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hg_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Hg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Hg_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hg_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Hg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Tl_sensor_letter = object {Tl_letter scale (0.75/(atom_min_radius + (((81 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Tl_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tl_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Tl_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Tl_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tl_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Tl_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Pb_sensor_letter = object {Pb_letter scale (0.75/(atom_min_radius + (((82 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Pb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pb_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pb_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Bi_sensor_letter = object {Bi_letter scale (0.75/(atom_min_radius + (((83 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Bi_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bi_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Bi_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Bi_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bi_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Bi_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Po_sensor_letter = object {Po_letter scale (0.75/(atom_min_radius + (((84 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Po_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Po_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Po_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Po_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Po_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Po_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare At_sensor_letter = object {At_letter scale (0.75/(atom_min_radius + (((85 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_At_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {At_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {At_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_At_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {At_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {At_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Rn_sensor_letter = object {Rn_letter scale (0.75/(atom_min_radius + (((86 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Rn_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rn_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Rn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Rn_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rn_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Rn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Fr_sensor_letter = object {Fr_letter scale (0.75/(atom_min_radius + (((87 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Fr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Fr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Fr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Fr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ra_sensor_letter = object {Ra_letter scale (0.75/(atom_min_radius + (((88 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ra_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ra_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ra_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ra_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ra_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ra_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Ac_sensor_letter = object {Ac_letter scale (0.75/(atom_min_radius + (((89 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Ac_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ac_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ac_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ac_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ac_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Ac_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Th_sensor_letter = object {Th_letter scale (0.75/(atom_min_radius + (((90 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Th_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Th_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Th_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Th_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Th_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Th_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Pa_sensor_letter = object {Pa_letter scale (0.75/(atom_min_radius + (((91 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Pa_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pa_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pa_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pa_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pa_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pa_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare U_sensor_letter = object {U_letter scale (0.75/(atom_min_radius + (((92 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_U_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {U_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {U_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_U_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {U_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {U_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Np_sensor_letter = object {Np_letter scale (0.75/(atom_min_radius + (((93 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Np_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Np_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Np_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Np_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Np_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Np_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Pu_sensor_letter = object {Pu_letter scale (0.75/(atom_min_radius + (((94 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Pu_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pu_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pu_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pu_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Pu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Am_sensor_letter = object {Am_letter scale (0.75/(atom_min_radius + (((95 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Am_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Am_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Am_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Am_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Am_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Am_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Cm_sensor_letter = object {Cm_letter scale (0.75/(atom_min_radius + (((96 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Cm_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cm_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cm_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cm_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Bk_sensor_letter = object {Bk_letter scale (0.75/(atom_min_radius + (((97 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Bk_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bk_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Bk_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Bk_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bk_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Bk_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Cf_sensor_letter = object {Cf_letter scale (0.75/(atom_min_radius + (((98 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Cf_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cf_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cf_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cf_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Cf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Es_sensor_letter = object {Es_letter scale (0.75/(atom_min_radius + (((99 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Es_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Es_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Es_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Es_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Es_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Es_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Fm_sensor_letter = object {Fm_letter scale (0.75/(atom_min_radius + (((100 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Fm_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fm_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Fm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Fm_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fm_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Fm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Md_sensor_letter = object {Md_letter scale (0.75/(atom_min_radius + (((101 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Md_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Md_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Md_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Md_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Md_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Md_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare No_sensor_letter = object {No_letter scale (0.75/(atom_min_radius + (((102 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_No_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {No_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {No_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_No_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {No_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {No_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Lr_sensor_letter = object {Lr_letter scale (0.75/(atom_min_radius + (((103 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Lr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Lr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Lr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Lr_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Lr_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Lr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Rf_sensor_letter = object {Rf_letter scale (0.75/(atom_min_radius + (((104 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Rf_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rf_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Rf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Rf_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rf_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Rf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Db_sensor_letter = object {Db_letter scale (0.75/(atom_min_radius + (((105 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Db_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Db_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Db_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Db_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Db_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Db_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Sg_sensor_letter = object {Sg_letter scale (0.75/(atom_min_radius + (((106 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Sg_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sg_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sg_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sg_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Bh_sensor_letter = object {Bh_letter scale (0.75/(atom_min_radius + (((107 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Bh_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bh_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Bh_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Bh_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bh_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Bh_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Hs_sensor_letter = object {Hs_letter scale (0.75/(atom_min_radius + (((108 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Hs_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hs_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Hs_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Hs_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hs_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Hs_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Mt_sensor_letter = object {Mt_letter scale (0.75/(atom_min_radius + (((109 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Mt_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mt_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Mt_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Mt_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mt_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Mt_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// unknowns -- use 109 for size purposes
#declare Delta_sensor_letter = object {Delta_letter scale (0.75/(atom_min_radius + (((109 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Delta_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Delta_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Delta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Delta_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Delta_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Delta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Theta_sensor_letter = object {Theta_letter scale (0.75/(atom_min_radius + (((109 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Theta_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Theta_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Theta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Theta_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Theta_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Theta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Sigma_sensor_letter = object {Sigma_letter scale (0.75/(atom_min_radius + (((109 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Sigma_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sigma_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sigma_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sigma_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sigma_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Sigma_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare Omega_sensor_letter = object {Omega_letter scale (0.75/(atom_min_radius + (((109 - 1) / 108) * (atom_max_radius - atom_min_radius))))}
#declare red_Omega_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Omega_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Omega_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Omega_sensor = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Omega_sensor_letter}
    texture {white_tex}
  }
  intersection {sphere {0, 1} object {Omega_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// now 113 more of the same thing but with "inactive" colorings
#declare red_H_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {H_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {H_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_H_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {H_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {H_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_He_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {He_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {He_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_He_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {He_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {He_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Li_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Li_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Li_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Li_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Li_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Li_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Be_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Be_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Be_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Be_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Be_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Be_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_B_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {B_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {B_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_B_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {B_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {B_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_C_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {C_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {C_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_C_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {C_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {C_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_N_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {N_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {N_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_N_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {N_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {N_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_O_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {O_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {O_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_O_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {O_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {O_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_F_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {F_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {F_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_F_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {F_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {F_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ne_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ne_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ne_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ne_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ne_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ne_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Na_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Na_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Na_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Na_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Na_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Na_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Mg_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mg_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Mg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Mg_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mg_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Mg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Al_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Al_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Al_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Al_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Al_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Al_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Si_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Si_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Si_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Si_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Si_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Si_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_P_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {P_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {P_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_P_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {P_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {P_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_S_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {S_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {S_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_S_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {S_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {S_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Cl_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cl_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cl_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cl_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cl_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cl_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ar_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ar_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ar_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ar_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ar_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ar_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_K_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {K_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {K_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_K_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {K_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {K_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ca_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ca_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ca_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ca_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ca_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ca_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Sc_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sc_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sc_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sc_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sc_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sc_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ti_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ti_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ti_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ti_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ti_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ti_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_V_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {V_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {V_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_V_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {V_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {V_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Cr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Mn_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mn_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Mn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Mn_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mn_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Mn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Fe_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fe_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Fe_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Fe_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fe_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Fe_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Co_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Co_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Co_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Co_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Co_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Co_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ni_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ni_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ni_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ni_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ni_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ni_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Cu_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cu_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cu_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cu_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Zn_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Zn_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Zn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Zn_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Zn_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Zn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ga_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ga_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ga_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ga_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ga_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ga_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ge_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ge_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ge_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ge_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ge_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ge_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_As_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {As_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {As_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_As_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {As_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {As_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Se_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Se_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Se_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Se_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Se_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Se_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Br_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Br_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Br_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Br_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Br_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Br_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Kr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Kr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Kr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Kr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Kr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Kr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Rb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Rb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Rb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Rb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Sr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Y_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Y_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Y_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Y_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Y_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Y_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Zr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Zr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Zr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Zr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Zr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Zr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Nb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Nb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Nb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Nb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Nb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Nb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Mo_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mo_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Mo_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Mo_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mo_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Mo_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Tc_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tc_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Tc_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Tc_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tc_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Tc_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ru_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ru_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ru_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ru_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ru_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ru_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Rh_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rh_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Rh_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Rh_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rh_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Rh_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Pd_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pd_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pd_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pd_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ag_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ag_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ag_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ag_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ag_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ag_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Cd_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cd_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cd_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cd_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_In_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {In_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {In_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_In_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {In_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {In_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Sn_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sn_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sn_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sn_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Sb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Te_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Te_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Te_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Te_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Te_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Te_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_I_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {I_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {I_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_I_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {I_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {I_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Xe_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Xe_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Xe_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Xe_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Xe_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Xe_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Cs_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cs_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cs_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cs_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cs_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cs_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ba_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ba_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ba_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ba_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ba_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ba_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_La_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {La_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {La_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_La_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {La_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {La_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ce_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ce_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ce_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ce_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ce_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ce_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Pr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Nd_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Nd_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Nd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Nd_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Nd_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Nd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Pm_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pm_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pm_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pm_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Sm_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sm_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sm_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sm_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Eu_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Eu_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Eu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Eu_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Eu_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Eu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Gd_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Gd_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Gd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Gd_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Gd_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Gd_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Tb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Tb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Tb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Tb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Dy_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Dy_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Dy_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Dy_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Dy_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Dy_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ho_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ho_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ho_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ho_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ho_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ho_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Er_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Er_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Er_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Er_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Er_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Er_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Tm_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tm_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Tm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Tm_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tm_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Tm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Yb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Yb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Yb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Yb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Yb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Yb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Lu_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Lu_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Lu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Lu_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Lu_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Lu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Hf_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hf_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Hf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Hf_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hf_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Hf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ta_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ta_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ta_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ta_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_W_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {W_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {W_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_W_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {W_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {W_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Re_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Re_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Re_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Re_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Re_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Re_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Os_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Os_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Os_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Os_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Os_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Os_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ir_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ir_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ir_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ir_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ir_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ir_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Pt_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pt_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pt_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pt_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pt_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pt_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Au_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Au_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Au_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Au_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Au_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Au_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Hg_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hg_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Hg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Hg_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hg_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Hg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Tl_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tl_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Tl_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Tl_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Tl_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Tl_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Pb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pb_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pb_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pb_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Bi_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bi_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Bi_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Bi_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bi_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Bi_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Po_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Po_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Po_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Po_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Po_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Po_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_At_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {At_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {At_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_At_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {At_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {At_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Rn_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rn_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Rn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Rn_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rn_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Rn_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Fr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Fr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Fr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Fr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ra_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ra_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ra_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ra_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ra_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ra_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Ac_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ac_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ac_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Ac_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Ac_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Ac_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Th_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Th_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Th_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Th_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Th_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Th_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Pa_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pa_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pa_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pa_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pa_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pa_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_U_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {U_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {U_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_U_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {U_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {U_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Np_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Np_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Np_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Np_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Np_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Np_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Pu_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pu_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Pu_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Pu_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Pu_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Am_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Am_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Am_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Am_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Am_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Am_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Cm_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cm_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cm_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cm_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Bk_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bk_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Bk_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Bk_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bk_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Bk_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Cf_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cf_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Cf_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Cf_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Cf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Es_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Es_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Es_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Es_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Es_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Es_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Fm_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fm_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Fm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Fm_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Fm_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Fm_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Md_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Md_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Md_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Md_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Md_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Md_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_No_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {No_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {No_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_No_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {No_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {No_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Lr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Lr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Lr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Lr_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Lr_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Lr_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Rf_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rf_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Rf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Rf_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Rf_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Rf_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Db_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Db_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Db_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Db_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Db_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Db_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Sg_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sg_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sg_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sg_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sg_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Bh_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bh_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Bh_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Bh_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Bh_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Bh_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Hs_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hs_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Hs_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Hs_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Hs_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Hs_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Mt_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mt_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Mt_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Mt_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Mt_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Mt_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Delta_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Delta_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Delta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Delta_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Delta_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Delta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Theta_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Theta_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Theta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Theta_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Theta_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Theta_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Sigma_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sigma_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sigma_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Sigma_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Sigma_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Sigma_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

#declare red_Omega_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_red_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Omega_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Omega_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}
#declare blue_Omega_sensor_inactive = union
{
  difference {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75} texture {dull_blue_tex}}
  difference
  {
    intersection {sphere {0, 1} cylinder {<0, 0, -10>, <0, 0, 10>, 0.75}}
    object {Omega_sensor_letter}
    texture {dull_white_tex}
  }
  intersection {sphere {0, 1} object {Omega_sensor_letter} texture {black_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// quantum swap
#declare swap_word_stick = text {ttf "cyrvetic.ttf" "SWAP" 10 0 scale <0.7, 0.7, 1> translate <-1 + 0.05, -0.5 + 0.25, -5>}

#declare red_swap = union
{
  difference {sphere {0, 1} object {swap_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {swap_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_swap = union
{
  difference {sphere {0, 1} object {swap_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {swap_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// fuse
#declare fuse_word_stick = text {ttf "cyrvetic.ttf" "FUSE" 10 0 scale <0.75, 0.75, 1> translate <-1 + 0.1, -0.5 + 0.24, -5>}

#declare red_fuse = union
{
  difference {sphere {0, 1} object {fuse_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {fuse_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_fuse = union
{
  difference {sphere {0, 1} object {fuse_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {fuse_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// split
#declare split_word_stick = text {ttf "cyrvetic.ttf" "SPLIT" 10 0 scale <0.72, 0.72, 1> translate <-1 + 0.04, -0.5 + 0.25, -5>}

#declare red_split = union
{
  difference {sphere {0, 1} object {split_word_stick} texture {red_tex}}
  intersection {sphere {0, 1} object {split_word_stick} texture {white_tex}}
  scale 0.22
  translate <(1/3), (2/3), red_control_layer>
  no_shadow
}

#declare blue_split = union
{
  difference {sphere {0, 1} object {split_word_stick} texture {blue_tex}}
  intersection {sphere {0, 1} object {split_word_stick} texture {white_tex}}
  scale 0.22
  translate <(2/3), (1/3), blue_control_layer>
  no_shadow
}

// flip-flop
#declare flip_word_stick = text {ttf "cyrvetic.ttf" "FLIP" 10 0 scale <0.95, 0.95, 1> translate <-1 + 0.12, -0.5 + 0.15, -5>}
#declare flop_word_stick = text {ttf "cyrvetic.ttf" "FLOP" 10 0 scale <0.78, 0.78, 1> translate <-1 + 0.1, -0.5 + 0.23, -5>}

#declare red_flip_flop = union
{
  difference
  {
    union
    {
      difference {sphere {0, 1} object {flip_word_stick} texture {dull_red_tex}}
      intersection {sphere {0, 1} object {flip_word_stick} texture {dull_white_tex}}
    }
    plane {-z, 0}
  }
  difference
  {
    union
    {
      difference {sphere {0, 1} object {flop_word_stick} texture {red_tex}}
      intersection {sphere {0, 1} object {flop_word_stick} texture {white_tex}}
    }
    plane {-z, 0}
    rotate 180 * x
  }
  sphere {0, 1 scale <1, 1, 0.5> texture {dull_red_tex}}
  scale 0.22
  no_shadow
}
#declare red_flip_flop_off_flip = object {red_flip_flop translate <(1/3), (2/3), red_control_layer>}
#declare red_flip_flop_flip_to_flop = object {red_flip_flop rotate (sine_expand * (-180)) * x translate <(1/3), (2/3), red_control_layer>}
#declare red_flip_flop_on_flop = object {red_flip_flop rotate 180 * x translate <(1/3), (2/3), red_control_layer>}
#declare red_flip_flop_flop_to_flip = object {red_flip_flop rotate (180 - (sine_expand * 180)) * x translate <(1/3), (2/3), red_control_layer>}

#declare blue_flip_flop = union
{
  difference
  {
    union
    {
      difference {sphere {0, 1} object {flip_word_stick} texture {dull_blue_tex}}
      intersection {sphere {0, 1} object {flip_word_stick} texture {dull_white_tex}}
    }
    plane {-z, 0}
  }
  difference
  {
    union
    {
      difference {sphere {0, 1} object {flop_word_stick} texture {blue_tex}}
      intersection {sphere {0, 1} object {flop_word_stick} texture {white_tex}}
    }
    plane {-z, 0}
    rotate 180 * x
  }
  sphere {0, 1 scale <1, 1, 0.5> texture {dull_blue_tex}}
  scale 0.22
  no_shadow
}
#declare blue_flip_flop_off_flip = object {blue_flip_flop translate <(2/3), (1/3), blue_control_layer>}
#declare blue_flip_flop_flip_to_flop = object {blue_flip_flop rotate (sine_expand * (-180)) * x translate <(2/3), (1/3), blue_control_layer>}
#declare blue_flip_flop_on_flop = object {blue_flip_flop rotate 180 * x translate <(2/3), (1/3), blue_control_layer>}
#declare blue_flip_flop_flop_to_flip = object {blue_flip_flop rotate (180 - (sine_expand * 180)) * x translate <(2/3), (1/3), blue_control_layer>}

// further flip flop definitions -- the originals all rotate top-downward; the new ones will rotate in the direction of their redirect indicator
// (I will take the risk that no one looks at the back of a horizontally flipping flip flop at rest in the surface of a shiny atom)
#declare red_flip_flop_flip_to_flop_down = red_flip_flop_flip_to_flop
#declare red_flip_flop_flop_to_flip_down = red_flip_flop_flop_to_flip
#declare blue_flip_flop_flip_to_flop_down = blue_flip_flop_flip_to_flop
#declare blue_flip_flop_flop_to_flip_down = blue_flip_flop_flop_to_flip

#declare red_flip_flop_flip_to_flop_up = object {red_flip_flop rotate sine_expand * 180 * x translate <(1/3), (2/3), red_control_layer>}
#declare red_flip_flop_flop_to_flip_up = object {red_flip_flop rotate (180 + (sine_expand * 180)) * x translate <(1/3), (2/3), red_control_layer>}
#declare blue_flip_flop_flip_to_flop_up = object {blue_flip_flop rotate sine_expand * 180 * x translate <(2/3), (1/3), blue_control_layer>}
#declare blue_flip_flop_flop_to_flip_up = object {blue_flip_flop rotate (180 + (sine_expand * 180)) * x translate <(2/3), (1/3), blue_control_layer>}

#declare red_flip_flop_h = union
{
  difference
  {
    union
    {
      difference {sphere {0, 1} object {flip_word_stick} texture {dull_red_tex}}
      intersection {sphere {0, 1} object {flip_word_stick} texture {dull_white_tex}}
    }
    plane {-z, 0}
  }
  difference
  {
    union
    {
      difference {sphere {0, 1} object {flop_word_stick} texture {red_tex}}
      intersection {sphere {0, 1} object {flop_word_stick} texture {white_tex}}
    }
    plane {-z, 0}
    rotate 180 * y
  }
  sphere {0, 1 scale <1, 1, 0.5> texture {dull_red_tex}}
  scale 0.22
  no_shadow
}

#declare blue_flip_flop_h = union
{
  difference
  {
    union
    {
      difference {sphere {0, 1} object {flip_word_stick} texture {dull_blue_tex}}
      intersection {sphere {0, 1} object {flip_word_stick} texture {dull_white_tex}}
    }
    plane {-z, 0}
  }
  difference
  {
    union
    {
      difference {sphere {0, 1} object {flop_word_stick} texture {blue_tex}}
      intersection {sphere {0, 1} object {flop_word_stick} texture {white_tex}}
    }
    plane {-z, 0}
    rotate 180 * y
  }
  sphere {0, 1 scale <1, 1, 0.5> texture {dull_blue_tex}}
  scale 0.22
  no_shadow
}

#declare red_flip_flop_flip_to_flop_left = object {red_flip_flop_h rotate sine_expand * 180 * y translate <(1/3), (2/3), red_control_layer>}
#declare red_flip_flop_flop_to_flip_left = object {red_flip_flop_h rotate (180 + (sine_expand * 180)) * y translate <(1/3), (2/3), red_control_layer>}
#declare blue_flip_flop_flip_to_flop_left = object {blue_flip_flop_h rotate sine_expand * 180 * y translate <(2/3), (1/3), blue_control_layer>}
#declare blue_flip_flop_flop_to_flip_left = object {blue_flip_flop_h rotate (180 + (sine_expand * 180)) * y translate <(2/3), (1/3), blue_control_layer>}

#declare red_flip_flop_flip_to_flop_right = object {red_flip_flop_h rotate -(sine_expand * 180 * y) translate <(1/3), (2/3), red_control_layer>}
#declare red_flip_flop_flop_to_flip_right = object {red_flip_flop_h rotate -(180 + (sine_expand * 180)) * y translate <(1/3), (2/3), red_control_layer>}
#declare blue_flip_flop_flip_to_flop_right = object {blue_flip_flop_h rotate -(sine_expand * 180 * y) translate <(2/3), (1/3), blue_control_layer>}
#declare blue_flip_flop_flop_to_flip_right = object {blue_flip_flop_h rotate -(180 + (sine_expand * 180)) * y translate <(2/3), (1/3), blue_control_layer>}


// reactor devices

// bonder
#declare bonder_stick = union
{
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.9} cylinder {<0, 0, -11>, <0, 0, 11>, 0.65}}
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.4} cylinder {<0, 0, -11>, <0, 0, 11>, 0.3}}
  merge {box {<-0.15, -0.025, -10>, <0.15, 0.025, 10>} box {<-0.025, -0.15, -10>, <0.025, 0.15, 10>} box {<-0.15, -0.025, -10>, <0.15, 0.025, 10> translate -0.225 * y} translate 0.075 * y}
}

#declare bonder_join_stick = box{<-0.65, -0.05, -10>, <0.65, 0.05, 10>}

#declare bonder = intersection
{
  object {bonder_stick}
  box {<-5, -5, device_layer>, <5, 5, device_layer + 0.1>}
  scale <0.5, 0.5, 1>
  // translate <0.5, 0.5, 0>
  texture {gray_tex}
  no_shadow
}

#declare bonder_join = intersection
{
  object {bonder_join_stick}
  box{<-5, -5, device_layer>, <5, 5, device_layer + 0.1>}
  scale <0.5, 0.5, 1>
  texture {gray_tex}
  no_shadow
}

// sensor
#declare sensor_stick = union
{
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.9} cylinder {<0, 0, -11>, <0, 0, 11>, 0.64}}
  cylinder {<0, 0, -10>, <0, 0, 10>, 0.2}
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.35} cylinder {<0, 0, -11>, <0, 0, 11>, 0.3}}
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.5} cylinder {<0, 0, -11>, <0, 0, 11>, 0.42}}
}

#declare sensor = intersection
{
  object {sensor_stick}
  box {<-5, -5, device_layer>, <5, 5, device_layer + 0.1>}
  scale <0.5, 0.5, 1>
  // translate <0.5, 0.5, 0>
  texture {gray_tex}
  no_shadow
}

// fusion target
#declare fuse_drop = -0.2;
#declare fusion_target = merge
{
  difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.9} cylinder {<0, 0, -11>, <0, 0, 11>, 0.65} plane {-x, 0} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {gray_tex}}
  cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.2 translate 0.7 * x scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {gray_tex}}
  difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.9} cylinder {<0, 0, -11>, <0, 0, 11>, 0.65} plane {x, 0} cylinder {<0.7, 0, -10>, <0.7, 0, 10>, 0.2} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {dull_gray_tex}}
  difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.4} cylinder {<0, 0, -10>, <0, 0, 10>, 0.3} plane {-x, 0} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {gray_tex}}
  difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.22} plane {-x, 0} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {gray_tex}}
  box {<0, -0.05, device_layer>, <0.45, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {gray_tex}}
  difference {cylinder {<0, fuse_drop, device_layer>, <0, fuse_drop, device_layer + 0.1>, 0.9} plane {y, fuse_drop} cylinder {<0, fuse_drop, -10>, <0, fuse_drop, 10>, 0.65} cylinder {<-1, 0, -10>, <-1, 0, 10>, 0.9} cylinder {<1, 0, -10>, <1, 0, 10>, 0.9} scale <0.5, 0.5, 1> translate 0.5 * y texture {gray_tex}}
  difference {cylinder {<0, -fuse_drop, device_layer>, <0, -fuse_drop, device_layer + 0.1>, 0.9} plane {-y, fuse_drop} cylinder {<0, -fuse_drop, -10>, <0, -fuse_drop, 10>, 0.65} cylinder {<-1, 0, -10>, <-1, 0, 10>, 0.9} cylinder {<1, 0, -10>, <1, 0, 10>, 0.9} scale <0.5, 0.5, 1> translate 0.5 * y texture {gray_tex}}
  difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.9} cylinder {<0, 0, -10>, <0, 0, 10>, 0.65} scale <0.5, 0.5, 1> translate <0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.975, -0.05, device_layer>, <-0.5, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> translate <0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.975, -0.05, device_layer>, <-0.5, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> rotate 90 * z translate <0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.975, -0.05, device_layer>, <-0.5, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> rotate 180 * z translate <0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.975, -0.05, device_layer>, <-0.5, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> rotate -90 * z translate <0.5, 0.5, 0> texture {gray_tex}}
  difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.4} cylinder {<0, 0, -10>, <0, 0, 10>, 0.3} scale <0.5, 0.5, 1> translate <0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.35, -0.05, device_layer>, <0.35, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> translate <0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.05, -0.35, device_layer>, <0.05, 0.35, device_layer + 0.1> scale <0.5, 0.5, 1> translate <0.5, 0.5, 0> texture {gray_tex}}
  no_shadow
} 

// fission target
#declare fission_target = merge
{
  difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.9} cylinder {<0, 0, -10>, <0, 0, 10>, 0.65} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.975, -0.05, device_layer>, <-0.5, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.975, -0.05, device_layer>, <-0.5, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> rotate 90 * z translate <-0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.975, -0.05, device_layer>, <-0.5, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> rotate 180 * z translate <-0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.975, -0.05, device_layer>, <-0.5, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> rotate -90 * z translate <-0.5, 0.5, 0> texture {gray_tex}}
  difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.4} cylinder {<0, 0, -10>, <0, 0, 10>, 0.3} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.35, -0.05, device_layer>, <0.35, 0.05, device_layer + 0.1> scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {gray_tex}}
  box {<-0.05, -0.35, device_layer>, <0.05, 0.35, device_layer + 0.1> scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {gray_tex}}
  difference {cylinder {<0, fuse_drop, device_layer>, <0, fuse_drop, device_layer + 0.1>, 0.9} plane {y, fuse_drop} cylinder {<0, fuse_drop, -10>, <0, fuse_drop, 10>, 0.65} cylinder {<-1, 0, -10>, <-1, 0, 10>, 0.9} cylinder {<1, 0, -10>, <1, 0, 10>, 0.9} scale <0.5, 0.5, 1> translate 0.5 * y texture {gray_tex}}
  difference {cylinder {<0, -fuse_drop, device_layer>, <0, -fuse_drop, device_layer + 0.1>, 0.9} plane {-y, fuse_drop} cylinder {<0, -fuse_drop, -10>, <0, -fuse_drop, 10>, 0.65} cylinder {<-1, 0, -10>, <-1, 0, 10>, 0.9} cylinder {<1, 0, -10>, <1, 0, 10>, 0.9} scale <0.5, 0.5, 1> translate 0.5 * y texture {gray_tex}}
  difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.9} plane {-x, 0} cylinder {<0, 0, -10>, <0, 0, 10>, 0.65} scale <0.5, 0.5, 1> translate <0.5, 0.5, 0> texture {dull_gray_tex}}
  difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.9} plane {x, 0} cylinder {<0, 0, -10>, <0, 0, 10>, 0.65} scale <0.5, 0.5, 1> translate <0.5, 0.5, 0> texture {gray_tex}}
  no_shadow
}

// quantum tunnel
#declare quantum_tunnel_stick = union
{
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.9} cylinder {<0, 0, -11>, <0, 0, 11>, 0.65}}
  union
  {
    box {<-0.85, -0.09, -10>, <0.051, 0.09, 10>}
    prism {linear_spline linear_sweep 10, -10, 4, <0.05, 0.2>, <0.65, 0>, <0.05, -0.2>, <0.05, 0.2> rotate 90 * x}
    translate 0.375 * x
    rotate 30 * z
    translate -0.375 * x
  }
  union
  {
    box {<-0.85, -0.09, -10>, <0.051, 0.09, 10>}
    prism {linear_spline linear_sweep 10, -10, 4, <0.05, 0.2>, <0.65, 0>, <0.05, -0.2>, <0.05, 0.2> rotate 90 * x}
    translate 0.375 * x
    rotate -30 * z
    translate -0.375 * x
  }
}

#declare quantum_tunnel = intersection
{
  object {quantum_tunnel_stick}
  box {<-5, -5, device_layer>, <5, 5, device_layer + 0.1>}
  scale <0.5, 0.5, 1>
  // translate <0.5, 0.5, 0>
  texture {gray_tex}
  no_shadow
}

// bonds
#declare single_bond = cylinder
{
  <-1, 0, 0>, <1, 0, 0>, 0.12
  texture
  {
    pigment {rgb 0.5}
    finish
    {
      ambient 0.65
      specular 0.4
      roughness 0.025
      metallic
    }
  }
  no_shadow
  scale 0.5
}

#declare bond_arch_height = (1/3);
#declare bond_arch_radius = (((bond_arch_height * bond_arch_height) + 1) / (2 * bond_arch_height));
#declare bond_arch = difference
{
  torus {bond_arch_radius, 0.12 rotate 90 * x translate <0, bond_arch_height - bond_arch_radius, 0>}
  plane {y, 0}
  plane {x, -1}
  plane {-x, -1}
  texture
  {
    pigment {rgb 0.5}
    finish
    {
      ambient 0.65
      specular 0.4
      roughness 0.025
      metallic
    }
  }
  no_shadow
}

#declare double_bond = union
{
  object {bond_arch}
  object {bond_arch rotate 180 * x}
  scale 0.5
}

#declare triple_bond = union
{
  object {bond_arch rotate 90 * x}
  object {bond_arch rotate -30 * x}
  object {bond_arch rotate -150 * x}
  scale 0.5
}

// waldos
#declare red_waldo_closed = difference
{
  cylinder {<0, 0, waldo_layer - 0.01>, <0, 0, waldo_layer>, 0.9}
  cylinder {<0, 0, -10>, <0, 0, 10>, 0.7}
  texture {plain_red_tex}
  scale <0.5, 0.5, 1>
  // translate <0.5, 0.5, 0>
  no_shadow
}

#declare red_waldo_open = union
{
  difference {cylinder {<0, 0, waldo_layer - 0.01>, <0, 0, waldo_layer>, 0.9} cylinder {<0, 0, -10>, <0, 0, 10>, 0.7} plane {-x, 0} translate -0.1 * x}
  difference {cylinder {<0, 0, waldo_layer - 0.01>, <0, 0, waldo_layer>, 0.9} cylinder {<0, 0, -10>, <0, 0, 10>, 0.7} plane {x, 0} translate 0.1 * x}
  texture {plain_red_tex}
  scale <0.5, 0.5, 1>
  // translate <0.5, 0.5, 0>
  no_shadow
}

#declare blue_waldo_closed = difference
{
  cylinder {<0, 0, waldo_layer>, <0, 0, waldo_layer + 0.01>, 0.9}
  cylinder {<0, 0, -10>, <0, 0, 10>, 0.7}
  texture {plain_blue_tex}
  scale <0.5, 0.5, 1>
  // translate <0.5, 0.5, 0>
  no_shadow
}

#declare blue_waldo_open = union
{
  difference {cylinder {<0, 0, waldo_layer>, <0, 0, waldo_layer + 0.01>, 0.9} cylinder {<0, 0, -10>, <0, 0, 10>, 0.7} plane {-x, 0} translate -0.1 * x}
  difference {cylinder {<0, 0, waldo_layer>, <0, 0, waldo_layer + 0.01>, 0.9} cylinder {<0, 0, -10>, <0, 0, 10>, 0.7} plane {x, 0} translate 0.1 * x}
  texture {plain_blue_tex}
  scale <0.5, 0.5, 1>
  // translate <0.5, 0.5, 0>
  no_shadow
}


// a grid-like box to hold input/output labels
// (centered at 0, gonna need scaling)
#declare label_box = union
{
  object {straight_track translate <-1.5, 2, 0>}
  object {straight_track scale <2, 1, 1> translate <0, 2, 0>}
  object {straight_track translate <1.5, 2, 0>}
  object {straight_track translate <-1.5, 1, 0>}
  object {straight_track scale <2, 1, 1> translate <0, 1, 0>}
  object {straight_track translate <1.5, 1, 0>}
  object {straight_track translate <-1.5, 0, 0>}
  object {straight_track scale <2, 1, 1>}
  object {straight_track translate <1.5, 0, 0>}
  object {straight_track translate <-1.5, -1, 0>}
  object {straight_track scale <2, 1, 1> translate <0, -1, 0>}
  object {straight_track translate <1.5, -1, 0>}
  object {straight_track translate <-1.5, -2, 0>}
  object {straight_track scale <2, 1, 1> translate <0, -2, 0>}
  object {straight_track translate <1.5, -2, 0>}

  object {straight_track rotate 90 * z translate <-2, 1.5, 0>}
  object {straight_track rotate 90 * z scale <1, 2, 1> translate <-2, 0, 0>}
  object {straight_track rotate 90 * z translate <-2, -1.5, 0>}
  object {straight_track rotate 90 * z translate <-1, 1.5, 0>}
  object {straight_track rotate 90 * z scale <1, 2, 1> translate <-1, 0, 0>}
  object {straight_track rotate 90 * z translate <-1, -1.5, 0>}
  object {straight_track rotate 90 * z translate <0, 1.5, 0>}
  object {straight_track rotate 90 * z scale <1, 2, 1> translate <0, 0, 0>}
  object {straight_track rotate 90 * z translate <0, -1.5, 0>}
  object {straight_track rotate 90 * z translate <1, 1.5, 0>}
  object {straight_track rotate 90 * z scale <1, 2, 1> translate <1, 0, 0>}
  object {straight_track rotate 90 * z translate <1, -1.5, 0>}
  object {straight_track rotate 90 * z translate <2, 1.5, 0>}
  object {straight_track rotate 90 * z scale <1, 2, 1> translate <2, 0, 0>}
  object {straight_track rotate 90 * z translate <2, -1.5, 0>}
  
  texture
  {
    pigment {rgb 0.25}
    finish {ambient 0.35}
  }
}

// special effects

#declare gridbox_sfx_pad_stick = merge
{
  box {<0.015, 0.04, -10>, <0.985, 0.96, 10>}
  box {<0.04, 0.015, -10>, <0.96, 0.985, 10>}
  cylinder {<0.04, 0.04, -10>, <0.04, 0.04, 10>, 0.025}
  cylinder {<0.04, 0.96, -10>, <0.04, 0.96, 10>, 0.025}
  cylinder {<0.96, 0.04, -10>, <0.96, 0.04, 10>, 0.025}
  cylinder {<0.96, 0.96, -10>, <0.96, 0.96, 10>, 0.025}
}

#declare sfx_pad_stick = union
{
  object {gridbox_sfx_pad_stick translate <0, 0, 0>}
  object {gridbox_sfx_pad_stick translate <0, 1, 0>}
  object {gridbox_sfx_pad_stick translate <0, 2, 0>}
  object {gridbox_sfx_pad_stick translate <0, 3, 0>}
  object {gridbox_sfx_pad_stick translate <1, 0, 0>}
  object {gridbox_sfx_pad_stick translate <1, 1, 0>}
  object {gridbox_sfx_pad_stick translate <1, 2, 0>}
  object {gridbox_sfx_pad_stick translate <1, 3, 0>}
  object {gridbox_sfx_pad_stick translate <2, 0, 0>}
  object {gridbox_sfx_pad_stick translate <2, 1, 0>}
  object {gridbox_sfx_pad_stick translate <2, 2, 0>}
  object {gridbox_sfx_pad_stick translate <2, 3, 0>}
  object {gridbox_sfx_pad_stick translate <3, 0, 0>}
  object {gridbox_sfx_pad_stick translate <3, 1, 0>}
  object {gridbox_sfx_pad_stick translate <3, 2, 0>}
  object {gridbox_sfx_pad_stick translate <3, 3, 0>}
}

#declare alpha_flash_stick = merge
{
  object {sfx_pad_stick translate <-5, 0, 0>}
  text {ttf "times.ttf" letter_alpha 10 0 scale <2.5, 2.5, 1> translate <(0.45 - 4), 1.65, -5>}
  text {ttf "cyrvetic.ttf" "input" 10 0 scale <0.4, 0.4, 1> translate <(0.6 - 4), 1.2, -5>}
}

#declare red_alpha_flash = intersection
{
  object {red_pad_flash_intersect}
  object {alpha_flash_stick}
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.75 + (0.25 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_alpha_flash = intersection
{
  object {blue_pad_flash_intersect}
  object {alpha_flash_stick}
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.75 + (0.25 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare beta_flash_stick = merge
{
  object {sfx_pad_stick translate <-5, -4, 0>}
  text {ttf "times.ttf" letter_beta 10 0 scale <2, 2, 1> translate <(0.6 - 4), (0.5 - 3), -5>}
  text {ttf "cyrvetic.ttf" "input" 10 0 scale <0.4, 0.4, 1> translate <(0.85 - 4), (0.2 - 3), -5>}
}

#declare red_beta_flash = intersection
{
  object {red_pad_flash_intersect}
  object {beta_flash_stick}
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.75 + (0.25 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_beta_flash = intersection
{
  object {blue_pad_flash_intersect}
  object {beta_flash_stick}
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.75 + (0.25 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare psi_flash_stick = merge
{
  object {sfx_pad_stick translate <1, 0, 0>}
  text {ttf "times.ttf" letter_psi 10 0 scale <2, 2, 1> translate <2.4, 2, -5>}
  text {ttf "cyrvetic.ttf" "output" 10 0 scale <0.4, 0.4, 1> translate <2.45, 1.2, -5>}
}

#declare red_psi_flash = intersection
{
  object {red_pad_flash_intersect}
  object {psi_flash_stick}
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.75 + (0.25 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_psi_flash = intersection
{
  object {blue_pad_flash_intersect}
  object {psi_flash_stick}
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.75 + (0.25 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare omega_flash_stick = merge
{
  object {sfx_pad_stick translate <1, -4, 0>}
  text {ttf "times.ttf" letter_omega_small 10 0 scale <2.5, 2.5, 1> translate <2.27, (0.6 - 3), -5>}
  text {ttf "cyrvetic.ttf" "output" 10 0 scale <0.4, 0.4, 1> translate <2.45, (0.2 - 3), -5>}
}

#declare red_omega_flash = intersection
{
  object {red_pad_flash_intersect}
  object {omega_flash_stick}
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.75 + (0.25 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_omega_flash = intersection
{
  object {blue_pad_flash_intersect}
  object {omega_flash_stick}
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.75 + (0.25 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare big_psi_flash_stick = merge
{
  object {sfx_pad_stick translate <1, 0, 0>}
  object {sfx_pad_stick translate <1, -4, 0>}
  text {ttf "times.ttf" letter_psi 10 0 scale <2, 2, 1> translate <2.4, 0, -5>}
  text {ttf "cyrvetic.ttf" "output" 10 0 scale <0.4, 0.4, 1> translate <2.45, (0.2 - 1), -5>}
}

#declare red_big_psi_flash = intersection
{
  object {red_pad_flash_intersect}
  object {big_psi_flash_stick}
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.75 + (0.25 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_big_psi_flash = intersection
{
  object {blue_pad_flash_intersect}
  object {big_psi_flash_stick}
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.75 + (0.25 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare red_bonder_flash = intersection
{
  object {bonder_stick}
  object {red_sfx_intersect}
  scale <0.5, 0.5, 1>
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_bonder_flash = intersection
{
  object {bonder_stick}
  object {blue_sfx_intersect}
  scale <0.5, 0.5, 1>
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare red_bonder_join_flash = intersection
{
  object {bonder_join_stick}
  object {red_sfx_intersect}
  scale <0.5, 0.5, 1>
  translate <0.5, 0, 0>
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_bonder_join_flash = intersection
{
  object {bonder_join_stick}
  object {blue_sfx_intersect}
  scale <0.5, 0.5, 1>
  translate <0.5, 0, 0>
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare max_bonds_stick = union
{
  text {ttf "cyrvetic.ttf" "MAX" 10 0 scale <0.45, 0.45, 1> translate <-0.445, 0, -5>}
  text {ttf "cyrvetic.ttf" "BONDS" 10 0 scale <0.3, 0.3, 1> translate <-0.5, -0.25, -5>}
}

#declare red_max_bonds = intersection
{
  object {red_bond_report_intersect}
  object {max_bonds_stick}
  translate <0, quad_expand, 0>
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_max_bonds = intersection
{
  object {blue_bond_report_intersect}
  object {max_bonds_stick}
  translate <0, quad_expand, 0>
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare bond_plus_flash_stick = merge
{
  box {<-0.4, -0.1, -10>, <0.4, 0.1, 10>}
  box {<-0.1, -0.4, -10>, <0.1, 0.4, 10>}
}

#declare red_bond_plus_flash = intersection
{
  object {red_bond_report_intersect}
  object {bond_plus_flash_stick}
  scale <1 + cubic_expand, 1 + cubic_expand, 1>
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_bond_plus_flash = intersection
{
  object {blue_bond_report_intersect}
  object {bond_plus_flash_stick}
  scale <1 + cubic_expand, 1 + cubic_expand, 1>
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare bond_minus_flash_stick = box {<-0.4, -0.1, -10>, <0.4, 0.1, 10>}

#declare red_bond_minus_flash = intersection
{
  object {red_bond_report_intersect}
  object {bond_minus_flash_stick}
  scale <1 + cubic_expand, 1 + cubic_expand, 1>
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_bond_minus_flash = intersection
{
  object {blue_bond_report_intersect}
  object {bond_minus_flash_stick}
  scale <1 + cubic_expand, 1 + cubic_expand, 1>
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare sensor_flash_stick = union
{
  object {sensor_stick}
  difference
  {
    cylinder {<0, 0, -10>, <0, 0, 10>, 1.25 + mod_clock}
    cylinder {<0, 0, -11>, <0, 0, 11>, 1 + mod_clock}
  }
  scale <0.5, 0.5, 1>
}

#declare red_sensor_flash = intersection
{
  object {red_sfx_intersect}
  object {sensor_flash_stick}
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_sensor_flash = intersection
{
  object {blue_sfx_intersect}
  object {sensor_flash_stick}
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare laser_impact_wedge = difference
{
  box {<-0.5, -0.5, -10>, <0.55, 0.5, 10>}
  plane {y, 0 rotate -7.5 * z}
  plane {-y, 0 rotate 7.5 * z}
}

#declare laser_impact = merge
{
  object {laser_impact_wedge}
  object {laser_impact_wedge rotate 60 * z}
  object {laser_impact_wedge rotate 120 * z}
  object {laser_impact_wedge rotate 180 * z}
  object {laser_impact_wedge rotate 240 * z}
  object {laser_impact_wedge rotate 300 * z}
  object {laser_impact_wedge scale <1.3, 1.3, 1> rotate 30 * z}
  object {laser_impact_wedge scale <1.3, 1.3, 1> rotate 90 * z}
  object {laser_impact_wedge scale <1.3, 1.3, 1> rotate 150 * z}
  object {laser_impact_wedge scale <1.3, 1.3, 1> rotate 210 * z}
  object {laser_impact_wedge scale <1.3, 1.3, 1> rotate 270 * z}
  object {laser_impact_wedge scale <1.3, 1.3, 1> rotate 330 * z}
  scale <0.75 + (mod_clock * 0.75), 0.75 + (mod_clock * 0.75), 1>
}

#declare nuclear_laser = merge
{
  box {<-10, -0.2, -10>, <0, 0.2, 10>}
  object {laser_impact}
}

#declare fusion_stick = merge
{
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.9} cylinder {<0, 0, -11>, <0, 0, 11>, 0.65} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0>}
  cylinder {<0, 0, -10>, <0, 0, 10>, 0.2 translate 0.7 * x scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0>}
  // difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.9} cylinder {<0, 0, -11>, <0, 0, 11>, 0.65} plane {x, 0} cylinder {<0.7, 0, -10>, <0.7, 0, 10>, 0.2} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0> texture {dull_gray_tex}}
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.4} cylinder {<0, 0, -11>, <0, 0, 11>, 0.3} plane {-x, 0} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0>}
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.22} plane {-x, 0} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0>}
  box {<0, -0.05, -10>, <0.45, 0.05, 10> scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0>}
  difference {cylinder {<0, fuse_drop, -10>, <0, fuse_drop, 10>, 0.9} plane {y, fuse_drop} cylinder {<0, fuse_drop, -11>, <0, fuse_drop, 11>, 0.65} cylinder {<-1, 0, -11>, <-1, 0, 11>, 0.9} cylinder {<1, 0, -11>, <1, 0, 11>, 0.9} scale <0.5, 0.5, 1> translate 0.5 * y}
  difference {cylinder {<0, -fuse_drop, -10>, <0, -fuse_drop, 10>, 0.9} plane {-y, fuse_drop} cylinder {<0, -fuse_drop, -11>, <0, -fuse_drop, 11>, 0.65} cylinder {<-1, 0, -11>, <-1, 0, 11>, 0.9} cylinder {<1, 0, -11>, <1, 0, 11>, 0.9} scale <0.5, 0.5, 1> translate 0.5 * y}
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.9} cylinder {<0, 0, -11>, <0, 0, 11>, 0.65} scale <0.5, 0.5, 1> translate <0.5, 0.5, 0>}
  box {<-0.975, -0.05, -10>, <-0.5, 0.05, 10> scale <0.5, 0.5, 1> translate <0.5, 0.5, 0>}
  box {<-0.975, -0.05, -10>, <-0.5, 0.05, 10> scale <0.5, 0.5, 1> rotate 90 * z translate <0.5, 0.5, 0>}
  box {<-0.975, -0.05, -10>, <-0.5, 0.05, 10> scale <0.5, 0.5, 1> rotate 180 * z translate <0.5, 0.5, 0>}
  box {<-0.975, -0.05, -10>, <-0.5, 0.05, 10> scale <0.5, 0.5, 1> rotate -90 * z translate <0.5, 0.5, 0>}
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.4} cylinder {<0, 0, -11>, <0, 0, 11>, 0.3} scale <0.5, 0.5, 1> translate <0.5, 0.5, 0>}
  box {<-0.35, -0.05, -10>, <0.35, 0.05, 10> scale <0.5, 0.5, 1> translate <0.5, 0.5, 0>}
  box {<-0.05, -0.35, -10>, <0.05, 0.35, 10> scale <0.5, 0.5, 1> translate <0.5, 0.5, 0>}
} 

// put the right half of the pad at origin
#declare fusion_flash_stick = merge
{
  object {fusion_stick translate <-0.5, -0.5, 0>}
  object {nuclear_laser}
}

#declare red_fusion_flash = intersection
{
  object {red_sfx_intersect}
  object {fusion_flash_stick}
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_fusion_flash = intersection
{
  object {blue_sfx_intersect}
  object {fusion_flash_stick}
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare tunnel_bound_cylinder_stick = cylinder {<0, 0, -11>, <0, 0, 11>, 0.8999 scale <0.5, 0.5, 1>}

#declare tunnel_flash_ring_stick = difference
{
  cylinder {<0, 0, -10>, <0, 0, 10>, 1.25 + mod_clock}
  cylinder {<0, 0, -11>, <0, 0, 11>, 1 + mod_clock}
  scale <0.5, 0.5, 1>
}

#declare fission_stick = merge
{
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.9} cylinder {<0, 0, -11>, <0, 0, 11>, 0.65} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0>}
  box {<-0.975, -0.05, -10>, <-0.5, 0.05, 10> scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0>}
  box {<-0.975, -0.05, -10>, <-0.5, 0.05, 10> scale <0.5, 0.5, 1> rotate 90 * z translate <-0.5, 0.5, 0>}
  box {<-0.975, -0.05, -10>, <-0.5, 0.05, 10> scale <0.5, 0.5, 1> rotate 180 * z translate <-0.5, 0.5, 0>}
  box {<-0.975, -0.05, -10>, <-0.5, 0.05, 10> scale <0.5, 0.5, 1> rotate -90 * z translate <-0.5, 0.5, 0>}
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.4} cylinder {<0, 0, -11>, <0, 0, 11>, 0.3} scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0>}
  box {<-0.35, -0.05, -10>, <0.35, 0.05, 10> scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0>}
  box {<-0.05, -0.35, -10>, <0.05, 0.35, 10> scale <0.5, 0.5, 1> translate <-0.5, 0.5, 0>}
  difference {cylinder {<0, fuse_drop, -10>, <0, fuse_drop, 10>, 0.9} plane {y, fuse_drop} cylinder {<0, fuse_drop, -11>, <0, fuse_drop, 11>, 0.65} cylinder {<-1, 0, -11>, <-1, 0, 11>, 0.9} cylinder {<1, 0, -11>, <1, 0, 11>, 0.9} scale <0.5, 0.5, 1> translate 0.5 * y}
  difference {cylinder {<0, -fuse_drop, -10>, <0, -fuse_drop, 10>, 0.9} plane {-y, fuse_drop} cylinder {<0, -fuse_drop, -11>, <0, -fuse_drop, 11>, 0.65} cylinder {<-1, 0, -11>, <-1, 0, 11>, 0.9} cylinder {<1, 0, -11>, <1, 0, 11>, 0.9} scale <0.5, 0.5, 1> translate 0.5 * y}
  // difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.9} plane {-x, 0} cylinder {<0, 0, -10>, <0, 0, 10>, 0.65} scale <0.5, 0.5, 1> translate <0.5, 0.5, 0> texture {dull_gray_tex}}
  // difference {cylinder {<0, 0, device_layer>, <0, 0, device_layer + 0.1>, 0.9} plane {x, 0} cylinder {<0, 0, -10>, <0, 0, 10>, 0.65} scale <0.5, 0.5, 1> translate <0.5, 0.5, 0> texture {gray_tex}}
  difference {cylinder {<0, 0, -10>, <0, 0, 10>, 0.9} cylinder {<0, 0, -11>, <0, 0, 11>, 0.65} scale <0.5, 0.5, 1> translate <0.5, 0.5, 0>}
  // no_shadow
}

#declare fission_flash_stick = merge
{
  object {fission_stick translate <0.5, -0.5, 0>}
  object {nuclear_laser}
}

#declare red_fission_flash = intersection
{
  object {red_sfx_intersect}
  object {fission_flash_stick}
  texture
  {
    pigment {rgbt <1, 0.025, 0.075, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}

#declare blue_fission_flash = intersection
{
  object {blue_sfx_intersect}
  object {fission_flash_stick}
  texture
  {
    pigment {rgbt <0.3, 0.3, 1, 0.5 + (0.5 * mod_clock)>}
    finish {ambient 1}
  }
  no_shadow
}
