# tikz3D

[![Build Status](https://travis-ci.org/njanetos/tikz3d.svg?branch=master)](https://travis-ci.org/njanetos/tikz3d)
[![Coverage Status](https://coveralls.io/repos/njanetos/tikz3d/badge.svg?branch=master&service=github)](https://coveralls.io/github/njanetos/tikz3d?branch=master)

Converts 3d specified tikz files into 2d tikz files suitable for rendering.

## Installation

```
make
```

## Usage

Currently only supports simple polygons. Takes a text file with tikz code, but with 3D coordinates:

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
   \filldraw[red!78] (0.0176639, 14.7525) -- (-6.02147, 11.794) -- (0.0158339, 8.25517) -- (0.0176639, 14.7525);
   \filldraw[red!78] (0.0176639, 14.7525) -- (0.0158339, 8.25517) -- (6.05556, 11.7914) -- (0.0176639, 14.7525);
   \filldraw[red!78] (0.0139121, 1.43211) -- (-6.02147, 11.794) -- (-5.34839, 5.11444) -- (0.0139121, 1.43211);
   \filldraw[red!78] (0.0139121, 1.43211) -- (0.0158339, 8.25517) -- (-6.02147, 11.794) -- (0.0139121, 1.43211);
   \filldraw[red!21] (0.0139121, 1.43211) -- (6.05556, 11.7914) -- (5.37862, 5.11174) -- (0.0139121, 1.43211);
   \filldraw[red!21] (0.0139121, 1.43211) -- (0.0158339, 8.25517) -- (6.05556, 11.7914) -- (0.0139121, 1.43211);
\end{tikzpicture}
```

 See `test.pdf` for the final rendering.

