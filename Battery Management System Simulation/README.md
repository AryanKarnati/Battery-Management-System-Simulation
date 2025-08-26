# Virtual Battery Pack Simulator (C)

A small, educational C project that simulates a multi‑cell battery pack. It models:
- **OCV vs SoC vs Temperature** lookup with bilinear interpolation
- **Coulomb counting** with a simple charge efficiency term
- **Thermal behavior** with ambient cooling and adjacent‑cell coupling
- **Aging placeholder** to track calendar age hours
- Hook for **fault injection**

This is intentionally lightweight and portable—no external dependencies, just a C compiler.

## Build & Run

```bash
make            # builds the simulator
./bms_sim       # emits CSV to stdout
```

The CSV columns are: `t_s, pack_current_a, v0..vN, temp0..tempN, soc0..socN`.

To run basic tests:
```bash
make test
```

## File Structure
```
include/        # headers
src/            # implementation (sim core + OCV/thermal/aging/faults)
test/           # tiny assert-based sanity tests
Makefile
README.md
```
## What this demonstrates
- Clean C module boundaries and headers
- Deterministic numerical simulation loop (fixed ∆t)
- Interpolation tables and basic thermal RC thinking
- Sensible Makefile, test target, and .gitignore
