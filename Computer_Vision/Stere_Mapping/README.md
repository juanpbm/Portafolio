# **Stereo Depth Mapping using the Fundamental Matrix to Reduce the Search Space**

## Abstract 

In this project, we used our previous Harris corner detector and non-max suppression algorithm to find point correspondences between a stereo image pair. The corners between the two images are then correlated with a normalized cross-correlation to generate pairs of corners with the highest NCC score. We then use RANSAC to estimate the fundamental matrix between the two images. The fundamental matrix allows us to drastically reduce the search space for finding correspondences on the right images for every pixel on the left. With these correspondences, we find the x and y disparity for each pixel and plot them as depth maps. 

For more information on this project, please refer to the [Report PDF.](Repoer.pdf)
