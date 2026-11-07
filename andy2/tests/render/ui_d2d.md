# UI tests: colour, texture, transparency (Direct2D)

Each object is added to an empty drawing, selected with a mouse click on its outline (Select tool), then: fill colour = right click on a colour-bar swatch; texture = click on a pattern-bar button (its source set to the test checker); tiling and blend modes = Format > Texture menu items (checked enabled first); transparency = Format > Transparency, slider dragged to 50, OK. Pixels are read back from the window.

Colour-bar swatch used: #000080. Pattern button: found.

| Object | Case | Result |
| --- | --- | --- |
| rectangle | solid colour | PASS |
| rectangle | colour, 50% transparency | PASS |
| rectangle | texture | PASS |
| rectangle | texture, 50% transparency | PASS |
| rectangle | tiled texture | PASS |
| rectangle | texture, multiply with fill colour | PASS |
| rectangle | texture, decal at 50% | PASS |
| rectangle | texture, fill colour only | PASS |
| circle | solid colour | PASS |
| circle | colour, 50% transparency | PASS |
| circle | texture | PASS |
| circle | texture, 50% transparency | PASS |
| circle | tiled texture | PASS |
| circle | texture, multiply with fill colour | PASS |
| circle | texture, decal at 50% | PASS |
| circle | texture, fill colour only | PASS |
| polygon | solid colour | PASS |
| polygon | colour, 50% transparency | PASS |
| polygon | texture | PASS |
| polygon | texture, 50% transparency | PASS |
| polygon | tiled texture | PASS |
| polygon | texture, multiply with fill colour | PASS |
| polygon | texture, decal at 50% | PASS |
| polygon | texture, fill colour only | PASS |
| image | solid colour | PASS |
| image | colour, 50% transparency | PASS |
| image | texture | PASS |
| image | texture, 50% transparency | PASS |
| image | tiled texture | PASS |
| image | texture, multiply with fill colour | PASS |
| image | texture, decal at 50% | PASS |
| image | texture, fill colour only | PASS |
| block (rectangle inside) | solid colour | PASS |
| block (rectangle inside) | colour, 50% transparency | PASS |
| block (rectangle inside) | texture | PASS |
| block (rectangle inside) | texture, 50% transparency | PASS |
| block (rectangle inside) | tiled texture | PASS |
| block (rectangle inside) | texture, multiply with fill colour | PASS |
| block (rectangle inside) | texture, decal at 50% | PASS |
| block (rectangle inside) | texture, fill colour only | PASS |

40 of 40 pass.
