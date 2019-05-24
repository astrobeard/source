
all: dataframe.so 

.PHONY: dataframe.so clean 

dataframe.so: 
	$(MAKE) -C ultra/dataframe/src/ 

clean: 
	$(MAKE) -C ultra/dataframe/ clean 
	$(MAKE) -C ultra/dataframe/src/ clean 
	rm -rf build 

