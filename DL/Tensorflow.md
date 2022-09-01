# Gradient 

The embedding layer is implemented as K.gather which is not differentiable, so there is no gradient.