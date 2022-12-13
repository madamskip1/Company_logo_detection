%    Params    %
fileName = "test.txt";
columns = [0 1 6];
%%%%%%%%%%%%%%%%


columns = columns + 1;

close all
close all hidden

numOfMoments = 10;

format long;
fileID = fopen(fileName);
[A, c] = fscanf(fileID, "%f;%f;%f;%f;%f;%f;%f;%f;%f;%f\n", [numOfMoments Inf]);

xAxisLength = c / numOfMoments;
xAxis = 1 : xAxisLength;

columnsLength = length(columns);
figure
hold on

if columnsLength == 1
    huValues = A(columns(1), :);
    plot(xAxis, huValues);
    stdVal = std(huValues);
    yline(stdVal, "-", "STD", 'LineWidth', 3);
    meanVal = mean(huValues);
    yline(meanVal, "-", "Mean", 'LineWidth', 3);
    medianVal = median(huValues);
    yline(medianVal, "-", "Median", 'LineWidth', 3);
    momentsLegend = strcat("Moment ", string(columns(1) - 1));
    stdLegend = strcat("STD = ", string(stdVal));
    meanLegend = strcat("Mean = ", string(meanVal));
    medianLegend = strcat("Median = ", string(medianVal));
    legend([momentsLegend stdLegend meanLegend medianLegend]);
else
    if columnsLength == 0
        columns = 1:numOfMoments;
        columnsLength = numOfMoments;
    end

    for c = 1:columnsLength
        plot(xAxis, A(c, :));
    end
    legendStrings = [];
    for c = 1:columnsLength
        legendStrings = [legendStrings strcat("Moment ", string(c - 1))];
    end
    legend(legendStrings);

end

hold off