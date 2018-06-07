Opis działania programu: 
Program otwiera plik wav podany w parametrze wywołania programu, następnie czyta z niego nagłówek oraz próbki.
Generuje klucz RSA oraz szyfruje plik do pliku test_encoded.wav
Deszyfruje plik i zapisuje do test_decoded.wav.

Klucz RSA generowany przez program jest losowy i składa się z 256 bitów.

Opis użytego algorytmu znajduje się w pliku opis.pdf
Do kompilacji programu potrzebny jest gcc-7 oraz biblioteka boost
