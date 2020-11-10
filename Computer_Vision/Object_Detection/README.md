# **Object Category Detection**

## Abstract

In this project, we implemented the generalized Hough transform to detect objects.  First, we used 550 pictures to train the algorithm. In this group of pictures, for each, we found corners using Harris corner detection and took a 25x25 patch around each corner to use them as the visual words. We then applied K-means to all these patches to make clusters of similar features to create our visual vocabulary. Moreover, the distance from each corner to the center of the training image (the center of the object) was recorded as the displacement. Finally, to find the object in a new image, we used SSD to match these clusters to corners in the new image and use the displacements to vote for the center of the object.  

For more information on this project, please refer to the [Report PDF.](Report.pdf)
