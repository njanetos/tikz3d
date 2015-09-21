# tikz3D 0.1

[![Project Status: Wip - Initial development is in progress, but there has not yet been a stable, usable release suitable for the public.](https://img.shields.io/badge/status-WIP-yellow.svg)](https://img.shields.io/badge/status-WIP-yellow.svg) 
[![Build Status](https://travis-ci.org/njanetos/tikz3d.svg?branch=master)](https://travis-ci.org/njanetos/tikz3d)
[![Coverage Status](https://coveralls.io/repos/njanetos/tikz3d/badge.svg?branch=master&service=github)](https://coveralls.io/github/njanetos/tikz3d?branch=master)

Converts 3d specified tikz files into 2d tikz files suitable for rendering.

## Installation

Run the makefile:

```
make
```

## Usage

Currently supports polygons and lines. Also has convinience functions for drawing boxes and rectangle. Takes a text file with tikz code, but with 3D coordinates, e.g.,

```
\camera (48, 48, 48, -0.78540, 0, -0.78540);
\sun (150, 100, 50);

\filldraw[red] (0, 0, 12) -- (12, 0, 12) -- (12, 12, 12);
\filldraw[red] (0, 0, 12) -- (12, 12, 12) -- (0, 12, 12);

\filldraw[red] (12, 12, 0) -- (12, 0, 12) -- (12, 0, 0);
\filldraw[red] (12, 12, 0) -- (12, 12, 12) -- (12, 0, 12);

\filldraw[red] (12, 12, 0) -- (0, 12, 12) -- (0, 12, 0);
\filldraw[red] (12, 12, 0) -- (12, 12, 12) -- (0, 12, 12);
```

`\camera` sets the camera location. The first three coordinates are its position, the last three are its Euler rotation angles. `\sun` adds in a sun for lighting, at the given location, pointing at `(0, 0, 0)`.

Must have 3 points, and a color. Any other parameters currently will not work. Each shape faces in the counter-clockwise direction, e.g., the points defining each triangle should wind around counter-clockwise as you face it. Otherwise, it will still render, but it will be lit as if from the other side.

Then, if this is saved as, e.g., `test.tex`, run

```
./tikz3D test.tex
```

which produces `output.tex` containing a tikz file ready to be rendered.

```
\begin{tikzpicture}
   \filldraw[red!78] (0.0176639, 14.7525) -- (-6.02147, 11.794) -- (0.0158339, 8.25517) -- cycle;
   \filldraw[red!78] (0.0176639, 14.7525) -- (0.0158339, 8.25517) -- (6.05556, 11.7914) -- cycle;
   \filldraw[red!78] (0.0139121, 1.43211) -- (-6.02147, 11.794) -- (-5.34839, 5.11444) -- cycle;
   \filldraw[red!78] (0.0139121, 1.43211) -- (0.0158339, 8.25517) -- (-6.02147, 11.794) -- cycle;
   \filldraw[red!21] (0.0139121, 1.43211) -- (6.05556, 11.7914) -- (5.37862, 5.11174) -- cycle;
   \filldraw[red!21] (0.0139121, 1.43211) -- (0.0158339, 8.25517) -- (6.05556, 11.7914) -- cycle;
\end{tikzpicture}
```

For convinience, there are some additional tikz-like functions supported. For example,

```
\camera (96, 96, 96, -0.78540, 0, -0.78540);
\sun (1, 1.5, 2);

\box[color=blue] (0, 0, 0) -- (3, 3, 3);
```

will draw a blue box:

[!["Blue box."](https://github.com/njanetos/tikz3d/raw/master/example.png)](https://github.com/njanetos/tikz3d/raw/master/example.png)

```
\camera (96, 96, 96, -0.78540, 0, -0.78540);
\sun (1, 1.5, 2);

\rectangle_x[color=blue] (3, -3) -- (6, 6)  (3);
```

will draw a rectangle, aligned along the `x`-axis. The first coordinate is the starting `y, z` coordinate, the second is the ending `y, z` coordinate. The last number is the position of the rectangle along the `x` axis. Similar functions called `\rectangle_y` and `\rectangle_z` draw rectangles aligned along the `y` and `z` axises.

### Binary space partitioning

Multiple items may not render the way you wish. For example,

```
\camera (96, 96, 96, -0.78540, 0, -0.78540);
\sun (1, 1.5, 2);

\rectangle_x[color=red] (3, -3) -- (6, 6, 3);

\box[color=green] (-1.5, -1.5, -1.5) -- (3.5, 3.5, 3.5);
```
will produce

[!["Broken."](https://github.com/njanetos/tikz3d/raw/master/example_no_bsp.png)](https://github.com/njanetos/tikz3d/raw/master/example_no_bsp.png)

The rectangle appears to be behind the box, even though it is intersecting, simply because the box was drawn second. To correct this, turn on binary space partitioning using `\bsp`:

```
\bsp[]

\camera (96, 96, 96, -0.78540, 0, -0.78540);
\sun (1, 1.5, 2);

\rectangle_x[color=red] (3, -3) -- (6, 6, 3);

\box[color=green] (-1.5, -1.5, -1.5) -- (3.5, 3.5, 3.5);
```

which produces

[!["Fixed."](https://github.com/njanetos/tikz3d/raw/master/example_bsp.png)](https://github.com/njanetos/tikz3d/raw/master/example_bsp.png)

Warning: Binary space partitioning will generally increase the number of tikz commands to be drawn in the output file by an order of magnitude.
