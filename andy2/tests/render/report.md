# Render tests: colour, texture, transparency

Each object gets its fill through the UI's own calls (colour toolbar: setLcolor; pattern buttons: setTexture; Transparency dialog: the "Transparency" notification at 50%), is drawn with GDI and with Direct2D, and pixels are checked against the intended result on a white background.

| Object | Case | GDI | Direct2D |
| --- | --- | --- | --- |
| rectangle | solid colour | PASS | PASS |
| rectangle | colour, 50% transparency | PASS | PASS |
| rectangle | texture | PASS | PASS |
| rectangle | texture, 50% transparency | PASS | PASS |
| rectangle | tiled texture | PASS | PASS |
| rectangle | texture, multiply with fill colour | PASS | PASS |
| rectangle | texture, decal at 50% | PASS | PASS |
| rectangle | texture, fill colour only | PASS | PASS |
| circle | solid colour | PASS | PASS |
| circle | colour, 50% transparency | PASS | PASS |
| circle | texture | PASS | PASS |
| circle | texture, 50% transparency | PASS | PASS |
| circle | tiled texture | PASS | PASS |
| circle | texture, multiply with fill colour | PASS | PASS |
| circle | texture, decal at 50% | PASS | PASS |
| circle | texture, fill colour only | PASS | PASS |
| polygon | solid colour | PASS | PASS |
| polygon | colour, 50% transparency | PASS | PASS |
| polygon | texture | PASS | PASS |
| polygon | texture, 50% transparency | PASS | PASS |
| polygon | tiled texture | PASS | PASS |
| polygon | texture, multiply with fill colour | PASS | PASS |
| polygon | texture, decal at 50% | PASS | PASS |
| polygon | texture, fill colour only | PASS | PASS |
| image | solid colour | PASS | PASS |
| image | colour, 50% transparency | PASS | PASS |
| image | texture | PASS | PASS |
| image | texture, 50% transparency | PASS | PASS |
| image | tiled texture | PASS | PASS |
| image | texture, multiply with fill colour | PASS | PASS |
| image | texture, decal at 50% | PASS | PASS |
| image | texture, fill colour only | PASS | PASS |
| block (rectangle inside) | solid colour | PASS | PASS |
| block (rectangle inside) | colour, 50% transparency | PASS | PASS |
| block (rectangle inside) | texture | PASS | PASS |
| block (rectangle inside) | texture, 50% transparency | PASS | PASS |
| block (rectangle inside) | tiled texture | PASS | PASS |
| block (rectangle inside) | texture, multiply with fill colour | PASS | PASS |
| block (rectangle inside) | texture, decal at 50% | PASS | PASS |
| block (rectangle inside) | texture, fill colour only | PASS | PASS |

GDI: 40 of 40 pass. Direct2D: 40 of 40 pass.
