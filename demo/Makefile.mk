helper: demo_huffman.cc ../src/huffman.cc
	g++ demo_huffman.cc ../src/huffman.cc -o demo_huffman
bzip2: ../src/run_length_encoding.cc ../src/BWT.cc ../src/move_to_front.cc ../src/huffman.cc demo.cc
	g++ ../src/run_length_encoding.cc ../src/BWT.cc ../src/move_to_front.cc ../src/huffman.cc demo.cc -o bzip2
all: helper bzip2