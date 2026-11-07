# UI tests: colour, texture, transparency (GDI)

Each object is added to an empty drawing, selected with a mouse click on its outline (Select tool), then: fill colour = right click on a colour-bar swatch; texture = click on a pattern-bar button (its source set to the test checker); transparency = Format > Transparency, slider dragged to 50, OK. Pixels are read back from the window.

Colour-bar swatch used: #000080. Pattern button: found.

| Object | Case | Result |
| --- | --- | --- |
| rectangle | solid colour | PASS |
| rectangle | colour, 50% transparency | PASS |
| rectangle | texture | PASS |
| rectangle | texture, 50% transparency | PASS |
| circle | solid colour | PASS |
| circle | colour, 50% transparency | PASS |
| circle | texture | PASS |
| circle | texture, 50% transparency | PASS |
| polygon | solid colour | PASS |
| polygon | colour, 50% transparency | PASS |
| polygon | texture | PASS |
| polygon | texture, 50% transparency | PASS |
| image | solid colour | PASS |
| image | colour, 50% transparency | PASS |
| image | texture | PASS |
| image | texture, 50% transparency | PASS |
| block (rectangle inside) | solid colour | PASS |
| block (rectangle inside) | colour, 50% transparency | PASS |
| block (rectangle inside) | texture | PASS |
| block (rectangle inside) | texture, 50% transparency | PASS |

20 of 20 pass. Tiling has no UI command (only the image file loader and code set it), so it is covered by the automated tests only.
