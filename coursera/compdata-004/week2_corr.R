corr <- function(directory, threshold = 0) {
        ## 'directory' is a character vector of length 1 indicating
        ## the location of the CSV files

        ## 'threshold' is a numeric vector of length 1 indicating the
        ## number of completely observed observations (on all
        ## variables) required to compute the correlation between
        ## nitrate and sulfate; the default is 0

        ## Return a numeric vector of correlations
	#directory <- "specdata"
	filenames <- list.files(directory, pattern="*.csv", full.names=TRUE);
	mode(filenames);
	n=1;
	rtn=c();
	for (i in seq_along(filenames)) {
		#id1=sprintf("%03d",as.numeric(i));
		#path=paste(directory,"/",id1,".csv",sep = '');
		con <- file(filenames[i], "r")
		data=read.csv(con)     
		close(con);
		cdata <-complete.cases(data);
		ddata=data[cdata,];
		if (nrow(ddata) >=threshold){
			x=(ddata[2]);
			y=(ddata[3]);
			rtn[n]=cor(x,y);
			n=n+1;
		}
	}
	if(n==1)
		rtn=as.numeric(c());
 	#m = data.frame(id=x,nobs=y)
	#return(m);
	#print(rtn);	
	return(rtn);
}
