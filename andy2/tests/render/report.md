# Render tests: colour, texture, transparency

Each object gets its fill through the UI's own calls (colour toolbar: setLcolor; pattern buttons: setTexture; Transparency dialog: the "Transparency" notification at 50%), is drawn with GDI and with Direct2D, and pixels are checked against the intended result on a white background.

| Object | Case | GDI | Direct2D |
| --- | --- | --- | --- |
| rectangle | solid colour | PASS | PASS |
| rectangle | colour, 50% transparency | PASS | PASS |
| rectangle | texture | PASS | PASS |
| rectangle | texture, 50% transparency | PASS | PASS |
| rectangle | tiled texture | PASS | PASS |
| circle | solid colour | PASS | PASS |
| circle | colour, 50% transparency | PASS | PASS |
| circle | texture | PASS | PASS |
| circle | texture, 50% transparency | PASS | PASS |
| circle | tiled texture | PASS | PASS |
| polygon | solid colour | PASS | PASS |
| polygon | colour, 50% transparency | PASS | PASS |
| polygon | texture | PASS | PASS |
| polygon | texture, 50% transparency | PASS | PASS |
| polygon | tiled texture | PASS | PASS |
| image | solid colour | PASS | PASS |
| image | colour, 50% transparency | PASS | PASS |
| image | texture | PASS | PASS |
| image | texture, 50% transparency | PASS | PASS |
| image | tiled texture | PASS | PASS |
| block (rectangle inside) | solid colour | PASS | PASS |
| block (rectangle inside) | colour, 50% transparency | PASS | PASS |
| block (rectangle inside) | texture | PASS | PASS |
| block (rectangle inside) | texture, 50% transparency | PASS | PASS |
| block (rectangle inside) | tiled texture | PASS | PASS |

GDI: 25 of 25 pass. Direct2D: 25 of 25 pass.
