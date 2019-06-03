
all: dataframe.so hlists.so 

.PHONY: dataframe.so hlists.so clean 

dataframe.so: 
	$(MAKE) -C ultra/dataframe/src/ 

hlists.so: 
	$(MAKE) -C ultra/nbody/src/ 

clean: 
	$(MAKE) -C ultra/dataframe/ clean 
	$(MAKE) -C ultra/dataframe/src/ clean 
	$(MAKE) -C ultra/nbody/ clean 
	$(MAKE) -C ultra/nbody/src/ clean 
	rm -rf build 

