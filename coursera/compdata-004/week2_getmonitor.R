complete <- function(directory, id = 1:332) {
        ## 'directory' is a character vector of length 1 indicating
        ## the location of the CSV files

        ## 'id' is an integer vector indicating the monitor ID numbers
        ## to be used
        
        ## Return a data frame of the form:
        ## id nobs
        ## 1  117
        ## 2  1041
        ## ...
        ## where 'id' is the monitor ID number and 'nobs' is the
        ## number of complete cases
	#m <- matrix(nrow = id, ncol = 2)
	directory <- "specdata"
	id1<-id
	x=c()
	y=c()
	n=1;
	for(i in id1) {
		id1=sprintf("%03d",as.numeric(i));
		path=paste(directory,"/",id1,".csv",sep = '');
		con <- file(path, "r")
		data=read.csv(con)     
		close(con);
		#print(path);
		#print(mode(data));
		cdata <-complete.cases(data);
		ddata=data[cdata,];
		#print(data[2]!='NA');
		x[n]<-i;
		y[n]<-nrow(ddata);
		n<-n+1;
		#s<-sum(data);
	}
 	m = data.frame(id=x,nobs=y)
	print(m);
	return(m);

}
