function segmented_images = kmeans_image_segmetnation( filename, iterations )
%kmeans_image_segmetnation Summary of this function goes here
%   Detailed explanation goes here

    % READ IN IMAGE AND CONVERT TO LAB COLORSPACE
    rgba_image = imread(filename);
    rgb_image = rgba_image(:,:,1:3);

    cform = makecform('srgb2lab');
    lab_image = applycform(rgb_image, cform);

    % PERFORM K-MEANS CLUSTERING
    ab = double(lab_image(:,:,2:3));
    nrows = size(ab,1);
    ncols = size(ab,2);
    ab = reshape(ab,nrows*ncols,2);
    nColors = 3;
    % repeat the clustering 3 times to avoid local minima
    [cluster_idx, cluster_center] = kmeans(ab,nColors,'distance','sqEuclidean', 'Replicates', iterations);

    % LABEL PIXELS
    pixel_labels = reshape(cluster_idx,nrows,ncols);
    segmented_images = cell(1,3);
    rgb_label = repmat(pixel_labels,[1 1 3]);

    for k = 1:nColors
        color = rgb_image;
        color(rgb_label ~= k) = 0;
        segmented_images{k} = color;
    end
    
%     SAVE IMAGES OUT
    for k = 1:nColors
        imwrite(segmented_images{k},sprintf('cluster_%d.tiff',k),'tiff');
    end
end

