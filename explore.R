library(plotly)

f <- matrix(flow[["v"]], ncol=99)
f <- 1/(1 - f)
plot_ly(z=~f) %>% add_surface()

# not very linear at low sepvals
sepval = 0.01
constsep<-filter(flow, sep<sepval+0.005,sep>sepval-0.005)
plot(constsep$mur,1/(1-constsep$v), type="l", main="sep=0.01", xlab="mu_r", ylab="1/(1-v) at interface")


intercept=c()
coefficient=c()

for (sepval in seq(0.10, 0.99, 0.01)) {
  constsep<-filter(flow, sep<sepval+0.005,sep>sepval-0.005)
  intercept[sepval*100] = coef(summary(lm((1/(1-constsep$v)) ~ constsep$mur)))[1]
  coefficient[sepval*100] = coef(summary(lm((1/(1-constsep$v)) ~ constsep$mur)))[2]
}

sepval=0.57
constsep<-filter(flow, sep<sepval+0.005,sep>sepval-0.005)
intercept[57] = coef(summary(lm((1/(1-constsep$v)) ~ constsep$mur)))[1]
coefficient[57] = coef(summary(lm((1/(1-constsep$v)) ~ constsep$mur)))[2]

sepval=0.58
constsep<-filter(flow, sep<sepval+0.005,sep>sepval-0.005)
intercept[58] = coef(summary(lm((1/(1-constsep$v)) ~ constsep$mur)))[1]
coefficient[58] = coef(summary(lm((1/(1-constsep$v)) ~ constsep$mur)))[2]

plot(seq(0.01, 0.99, 0.01), log(coefficient), type="l")
plot(seq(0.01, 0.99, 0.01), log(intercept), type="l")
