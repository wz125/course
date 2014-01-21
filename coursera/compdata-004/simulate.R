sim1<-function(){
	msg<- paste("\nSuppose we want to simulate from a Poisson model where\n",
		"y = β0 + β1x + ε\n",
		"where ε ∼ N (0, 22 ). Assume x ∼ N (0, 12 ), β0 = 0.5 and β1 = 2.\n")
	print(msg)
	set.seed(20)
	x <- rnorm(100)
	e <- rnorm(100, 0, 2)
	y <- 0.5 + 2 * x + e
	summary(y)
	plot(x, y,main = msg)
}

sim2<-function(){
	msg<- " What if x is binary?\n"
	set.seed(10)
	x <- rbinom(100, 1, 0.5)
	e <- rnorm(100, 0, 2)
	y <- 0.5 + 2 * x + e
	summary(y)
	plot(x, y,main=msg)
}

sim3<-function(){
msg<- paste("Suppose we want to simulate from a Poisson model where\n",
"	Y∼ Poisson(μ)\n",
"	log μ = β0 + β1 x\n",
"	and β0 = 0.5 and β1 = 0.3. We need to use the rpois function for this\n")
	set.seed(1)
	x <- rnorm(100)
	log.mu <- 0.5 + 0.3 * x
	y <- rpois(100, exp(log.mu))
	summary(y)
	plot(x, y,main=msg)
}





