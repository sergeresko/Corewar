.name "bocal"
.comment "Nulova terpimist do chitingu"

live:
	live %1
win:
	ld %45, r3
	zjmp %:live
	fork %5
