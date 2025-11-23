# LaTeX Report Documentation

This directory contains the LaTeX source files for the technical report of the Graph Algorithms with GRASP project.

## Files

- **report.tex**: Main LaTeX document containing the complete technical report
- **cover.tex**: Cover page template for UFJF
- **references.bib**: Bibliography file with references used in the report

## Compilation

### Using pdflatex (Recommended)

```bash
cd docs/latex
pdflatex report.tex
bibtex report
pdflatex report.tex
pdflatex report.tex
```

The compiled PDF will be generated as `report.pdf`.

### Using Overleaf (Online)

1. Upload all files to [Overleaf](https://www.overleaf.com/)
2. Set the main document to `report.tex`
3. Click "Recompile"

### Using Make (Optional)

If you have `make` installed, you can create a `Makefile`:

```makefile
all: report.pdf

report.pdf: report.tex cover.tex references.bib
	pdflatex report.tex
	bibtex report
	pdflatex report.tex
	pdflatex report.tex

clean:
	rm -f *.aux *.log *.bbl *.blg *.out *.toc *.lof *.lot

.PHONY: clean
```

Then compile with:
```bash
make
```

## Requirements

- LaTeX distribution (TeX Live, MiKTeX, or MacTeX)
- Required packages:
  - `amsmath`, `amsfonts`, `amssymb`, `amsthm`
  - `graphicx`
  - `hyperref`
  - `algorithm`, `algpseudocode`
  - `listings`
  - `geometry`
  - `babel` (English)

## Structure

The report includes:
1. Cover page (UFJF template)
2. Table of contents
3. Introduction
4. Literature review
5. Methodology
6. Implementation details
7. Results and analysis
8. Conclusion
9. References

## Notes

- The report follows UFJF academic standards
- All algorithms are documented with pseudocode
- Complexity analysis is included for all algorithms
- Bibliography uses BibTeX format

