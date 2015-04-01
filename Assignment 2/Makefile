all:
	git add -A .
	git commit -m "Phase 2:working on assignment 2" 
	# mkdir bin
	cp assgn2_bplus_data.txt bin/assgn2_bplus_data.txt
	cp a.txt bin/a.txt
	cp bplustree.config bin/bplustree.config
	cp mysol.cpp bin/mysol.cpp
	cp querysample.txt bin/querysample.txt
	g++ bin/mysol.cpp -o bin/mysol
	./bin/mysol
clean:
	rm -rf bin/
	mkdir bin