// Copyright (c) 2022, The MaPra Authors.

#ifndef UNIT_H_
#define UNIT_H_

namespace mapra {

inline constexpr unsigned int kNumRows = 6;
inline constexpr unsigned int kNumCols = 7;
inline constexpr unsigned int kNumGames = 5;

// difficulty 0 = Eingabe ueber die Tatstatur
void StartGame(unsigned int difficulty);

// Mit nextTurn uebergeben Sie die Nummer der Spalte (0...numCols-1),
// die Ihr Programm fuer den naechsten Spielstein ausgewaehlt hat.
// Zurueckgegeben wird Ihnen dann der naechste Zug der Praktikumsumgebung
// bzw. von der Tastatur.
int NextTurn(int column);

}  // namespace mapra

#endif  // UNIT_H_
