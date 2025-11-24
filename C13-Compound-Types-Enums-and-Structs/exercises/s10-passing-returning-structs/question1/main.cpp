#include <iostream>

struct AdsStats
{
    int seenAds {0};
    double clickThroughRate {0.0};
    double avgEarningsPerAd {0.0};
};

void printAdsStats(const AdsStats& stats)
{
    std::cout << "Seen Ads: " << stats.seenAds << '\n';
    std::cout << "Click Through Rate: " << stats.clickThroughRate << '\n';
    std::cout << "Average Earnings Per Ad: " << stats.avgEarningsPerAd << '\n';
    std::cout << "Today Earning: " << (stats.seenAds * stats.clickThroughRate * stats.avgEarningsPerAd) << '\n';
}

AdsStats getAdsStats()
{
    AdsStats tempStats {};
    std::cout << "Enter number of seen ads: ";
    std::cin >> tempStats.seenAds;
    std::cout << "Enter click through rate: ";
    std::cin >> tempStats.clickThroughRate;
    std::cout << "Enter average earnings per ad: ";
    std::cin >> tempStats.avgEarningsPerAd;
    return tempStats;
}

int main()
{
    AdsStats stats {getAdsStats()};
    printAdsStats(stats);
    return 0;
}