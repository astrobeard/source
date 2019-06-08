
all: dataframe.so hlists.so ultramath.so 

.PHONY: dataframe.so hlists.so ultramath.so clean 

dataframe.so: 
	$(MAKE) -C ultra/dataframe/src/ 

hlists.so: 
	$(MAKE) -C ultra/nbody/src/ 

ultramath.so: 
	$(MAKE) -C ultra/math/src/ 

clean: 
	$(MAKE) -C ultra/dataframe/ clean 
	$(MAKE) -C ultra/dataframe/src/ clean 
	$(MAKE) -C ultra/nbody/ clean 
	$(MAKE) -C ultra/nbody/src/ clean 
	$(MAKE) -C ultra/math/src/ clean 
	$(MAKE) -C ultra/math/ clean 
	rm -rf build 

