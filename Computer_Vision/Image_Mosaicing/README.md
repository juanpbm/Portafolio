# **Image Mosaicing using Harris Corner Detection and Estimation of Homography**

## Abstract 

In this project, we implemented our own Harris corner detector and non-max suppression algorithm to generate a sparse set of corners for an image. 
The corners between the two images are then correlated with a normalized cross-correlation to generate pairs of corners with the highest NCC score.
We then use RANSAC to estimate a homography between the two perspectives by randomly sampling four pairs to produce the best fit. With the homography,
we then warp the second image onto the first and merge the overlapping pixels to create the mosaic.

For more information on this project, please refer to the report PDF.
