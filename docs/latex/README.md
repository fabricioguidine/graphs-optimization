# LaTeX Technical Report - Compilation Instructions

## Prerequisites

- LaTeX distribution (TeX Live, MiKTeX, or MacTeX)
- Required packages:
  - `algorithm2e`
  - `amsmath`, `amssymb`
  - `graphicx`
  - `hyperref`
  - `booktabs`

## Compilation

### Method 1: Using pdflatex (Command Line)

```bash
cd docs/latex
pdflatex report.tex
bibtex report
pdflatex report.tex
pdflatex report.tex
```

This will generate `report.pdf` in the `docs/latex/` directory.

### Method 2: Using Overleaf (Online - Recommended)

1. Go to [Overleaf](https://www.overleaf.com/)
2. Create a new project
3. Upload all files from `docs/latex/`:
   - `report.tex`
   - `cover.tex`
   - `references.bib`
4. Compile using the "Recompile" button
5. Download the generated `report.pdf`

## Files Structure

- `report.tex` - Main LaTeX document
- `cover.tex` - Cover page with group members
- `references.bib` - Bibliography (BibTeX format)
- `report.pdf` - Compiled PDF (generated after compilation)

## Updating Results

After running algorithms, update the results tables in `report.tex` (Section 3.3) with:
- Execution times (in milliseconds)
- Solution quality metrics
- Number of iterations (for iterative algorithms)

## Date Information

- Repository creation date: November 2019
- Report follows UFJF technical report template standards
