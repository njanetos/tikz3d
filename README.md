# tikz3D

[![Build Status](https://travis-ci.org/njanetos/tikz3d.svg?branch=master)](https://travis-ci.org/njanetos/tikz3d)
[![Coverage Status](https://coveralls.io/repos/njanetos/tikz3d/badge.svg?branch=master&service=github)](https://coveralls.io/github/njanetos/tikz3d?branch=master)

Converts 3d specified tikz files into 2d tikz files suitable for rendering.

## Installation

```
make
```

## Usage

Currently only supports simple polygons from one camera direction and one lighting direction. Take a text file with tikz code, but with 3D coordinates:

```
\filldraw[red] (0, 0, 12) -- (12, 0, 12) -- (12, 12, 12);
\filldraw[red] (0, 0, 12) -- (12, 12, 12) -- (0, 12, 12);

\filldraw[blue] (12, 12, 0) -- (12, 0, 12) -- (12, 0, 0);
\filldraw[blue] (12, 12, 0) -- (12, 12, 12) -- (12, 0, 12);

\filldraw[green] (12, 12, 0) -- (0, 12, 12) -- (0, 12, 0);
\filldraw[green] (12, 12, 0) -- (12, 12, 12) -- (0, 12, 12);
```

Must have 3 points, and a color. Any other parameters currently will not work. Each shape faces in the counter-clockwise direction, e.g., the points defining each triangle should wind around counter-clockwise as you face it. Otherwise, it will still render, but it will be lit as if from the other side.

Then, if this is saved as, e.g., `test.tex`, run

```
./tikz3D test.tex
```

which produces `output.tex` containing the final rendering. See `test.pdf` for the final rendering.

