#pandoc -f markdown-raw_tex -t latex script.md -o script.tex

pandoc -f markdown-raw_tex --pdf-engine=xelatex \
    -V geometry:margin=1.5cm \
    -V mainfont="FiraSans-Regular" \
    -V monofont="Fantasque Sans Mono Italic Nerd Font Complete" \
    -V 'mainfontoptions:BoldFont=FiraSans-Bold, ItalicFont=FiraSans-Italic, BoldItalicFont=FiraSans-BoldItalic'  script.md -o script.pdf
