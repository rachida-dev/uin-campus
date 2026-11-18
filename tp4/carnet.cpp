#include "uincampus/saisie.hpp"

#include <algorithm>
#include <format>
#include <print>
#include <string_view>
#include <vector>

using uin::lireEntier;
using uin::lireNote;

namespace carnet {

enum class Ordre { Croissant, Decroissant };

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    int nbValidees{};
};

// ---------- Calculs : aucune entrée-sortie ----------

/// @pre notes n'est pas vide
[[nodiscard]] Statistiques calculerStatistiques(const std::vector<double>& notes)
{
    const auto [mini, maxi] = std::ranges::minmax(notes);
    double somme{0.0};
    int validees{0};
    for (double n : notes) {
        somme += n;
        if (n >= 10.0) {
            ++validees;
        }
    }
    return {mini, maxi, somme / static_cast<double>(notes.size()), validees};
}

void appliquerBonus(std::vector<double>& notes, double bonus)
{
    std::ranges::for_each(notes, [bonus](double& n) { n = std::clamp(n + bonus, 0.0, 20.0); });
}

void trier(std::vector<double>& notes, Ordre ordre)
{
   if (ordre == Ordre::Croissant) {
       std::ranges::sort(notes);
   } else {
       std::ranges::sort(notes, [](double a, double b) { return a > b; });
   }
}

// ---------- Interface utilisateur -----------

void afficherNotes(const std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note.");
        return;
    }
    for (std::size_t i{0}; i < notes.size(); ++i) {
        std::println("{:>3}. {:6.2f}", i + 1, notes[i]);
    }
}

void ajouter(std::vector<double>& notes)
{
    notes.push_back(lireNote("Note à ajouter : "));
}

void modifier(std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note à modifier.");
        return;
    }
    afficherNotes(notes);
    const int rang = lireEntier("Numéro de la note : ", 1, static_cast<int>(notes.size()));
    notes[static_cast<std::size_t>(rang - 1)] = lireNote("Nouvelle valeur : ");
}

void supprimer(std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note à supprimer.");
        return;
    }
    afficherNotes(notes);
    const int rang = lireEntier("Numéro de la note : ", 1, static_cast<int>(notes.size()));
    notes.erase(notes.begin() + (rang - 1));
}

void afficherStatistiques(const std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note.");
        return;
    }
    const auto [mini, maxi, moyenne, validees] = calculerStatistiques(notes);
    std::println("Min {:.2f} | Max {:.2f} | Moyenne {:.2f} | Validees {}/{}",
                 mini, maxi, moyenne, validees, notes.size());
}

[[nodiscard]] int afficherMenu()
{
    std::println("\n=== Carnet de notes ===");
    std::println("1. Ajouter une note\n2. Afficher les notes\n3. Modifier une note");
    std::println("4. Supprimer une note\n5. Trier les notes\n6. Statistiques");
    std::println("7. Appliquer un bonus\n0. Quitter");
    return lireEntier("Votre choix : ", 0, 7);
}

} // namespace carnet

int main()
{
    std::vector<double> notes;
    int choix{};
    do {
        choix = carnet::afficherMenu();
        switch (choix) {
        case 1: carnet::ajouter(notes); break;
        case 2: carnet::afficherNotes(notes); break;
        case 3: carnet::modifier(notes); break;
        case 4: carnet::supprimer(notes); break;
        case 5: {
            const int sens = lireEntier("1. Croissant 2. Décroissant : ", 1, 2);
            carnet::trier(notes, sens == 1 ? carnet::Ordre::Croissant : carnet::Ordre::Decroissant);
            break;
        }
        case 6: carnet::afficherStatistiques(notes); break;
        case 7: carnet::appliquerBonus(notes, lireNote("Bonus : ")); break;
        default: break;
        }
    } while (choix != 0);
}
