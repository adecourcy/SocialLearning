import matplotlib.pyplot as plt

if __name__ == "__main__":
  scores = [["0.974348", "0.965672", "0.958994", "0.958201",
             "0.955368", "0.956294", "0.953139"],

            ["0.998384", "0.991501", "0.949384", "0.888037",
             "0.821198", "0.790611", "0.769943"],

            ["0.898943", "0.783000", "0.668578", "0.588179",
             "0.506347", "0.454887", "0.406155"],

            ["0.995183", "0.973061", "0.875293", "0.764099",
             "0.649042", "0.561315", "0.484315"]]

  legend = ["Fastest Transmission",
            "Moderate Transmission - Original",
            "Moderate Transmission - SFI",
            "Low Transmission"]

  x = [1,2,3,4,5,6,7]

  for score in scores:
    plt.plot(x, score)

  plt.ylabel("Scores")
  plt.xlabel("K Value")
  plt.xticks(x, ["2", "4", "6", "8", "10", "12", "14"])

  plt.legend(legend)

  plt.show()