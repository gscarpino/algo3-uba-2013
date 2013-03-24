
.PHONY: all dot clean

PDF=Informe.TP2.AyEDIII.2012.C2.pdf
TEXFILES=ej1.tex ej2.tex introduccion.tex

# IMAGES=$(patsubst  %, image/%, ${IMAGE})

all: $(PDF)

$(PDF): *.tex
	texi2pdf Informe.TP2.AyEDIII.2012.C2.tex

clean:
	rm -f $(PDF) *.aux *.log *.toc 
