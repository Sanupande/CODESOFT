/*RECOMMENDATION SYSTEM
Create a simple recommendation system that suggests items tousers based on their preferences. You can use techniques like collaborative filtering or content-based filtering to recommendmovies, books, or products to users.*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// User-item interaction matrix
unordered_map<int, unordered_map<int, double>> userItemMatrix;

// User similarity matrix
unordered_map<int, unordered_map<int, double>> userSimilarityMatrix;

// Item similarity matrix
unordered_map<int, unordered_map<int, double>> itemSimilarityMatrix;

// Load the movie dataset
void loadMovieData() {
    // Load the movie dataset from a file or database
    // ...
    // Populate the user-item interaction matrix
    userItemMatrix = {
        {1, {{1, 5.0}, {2, 3.5}, {3, 4.0}}},
        {2, {{1, 4.0}, {3, 4.5}, {4, 2.0}}},
        {3, {{2, 3.0}, {3, 5.0}, {4, 3.5}, {5, 4.0}}},
        {4, {{1, 2.5}, {4, 4.0}, {5, 4.5}}}
    };
}

// Calculate user similarity matrix
void calculateUserSimilarity() {
    // Calculate user similarity matrix using Pearson correlation
    // ...
    userSimilarityMatrix = {
        {1, {{2, 0.8}, {3, 0.6}, {4, 0.4}}},
        {2, {{1, 0.8}, {3, 0.7}, {4, 0.3}}},
        {3, {{1, 0.6}, {2, 0.7}, {4, 0.5}, {5, 0.6}}},
        {4, {{1, 0.4}, {2, 0.3}, {3, 0.5}, {5, 0.8}}}
    };
}

// Calculate item similarity matrix
void calculateItemSimilarity() {
    // Calculate item similarity matrix using Pearson correlation
    // ...
    itemSimilarityMatrix = {
        {1, {{2, 0.7}, {3, 0.8}, {4, 0.3}}},
        {2, {{1, 0.7}, {3, 0.6}, {5, 0.5}}},
        {3, {{1, 0.8}, {2, 0.6}, {4, 0.4}, {5, 0.7}}},
        {4, {{1, 0.3}, {3, 0.4}, {5, 0.9}}},
        {5, {{2, 0.5}, {3, 0.7}, {4, 0.9}}}
    };
}

// Get top N recommendations for a user
vector<int> getTopNRecommendations(int userId, const unordered_map<int, unordered_map<int, double>>& itemSimilarityMatrix, int n) {
    // Get the user's rated movies
    unordered_map<int, double>& userRatings = userItemMatrix[userId];
    
    // Calculate the weighted average of similar movies
    unordered_map<int, double> similarMovies;
    for (const auto& rating : userRatings) {
        int movieId = rating.first;
        for (const auto& similarity : itemSimilarityMatrix.at(movieId)) {
            int similarMovieId = similarity.first;
            double similarityScore = similarity.second;
            if (userRatings.count(similarMovieId) == 0) {
                similarMovies[similarMovieId] += rating.second * similarityScore;
            }
        }
    }
    
    // Sort the movies by similarity score and get the top N
    vector<pair<int, double>> sortedMovies(similarMovies.begin(), similarMovies.end());
    sort(sortedMovies.begin(), sortedMovies.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
        return a.second > b.second;
    });
    
    vector<int> topNMovies;
    for (int i = 0; i < n && i < sortedMovies.size(); ++i) {
        topNMovies.push_back(sortedMovies[i].first);
    }
    
    return topNMovies;
}

int main() {
    // Load the movie dataset
    loadMovieData();
    
    // Calculate user similarity matrix
    calculateUserSimilarity();
    
    // Calculate item similarity matrix
    calculateItemSimilarity();
    
    // Get top 3 recommendations for user 1
    int userId = 1;
    int n = 3;
    vector<int> recommendations = getTopNRecommendations(userId, itemSimilarityMatrix, n);
    
    // Print the recommendations
    cout << "Top " << n << " recommendations for user " << userId << ":" << endl;
    for (int movieId : recommendations) {
        cout << movieId << endl;
    }
    
    return 0;
}