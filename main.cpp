/*
#include "mainwindow.h"
#include "multipleViewsWindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	// Création de l'application Qt
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
*/

/*
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
int main()
{
  try
  {
    // Create an instance.
    mongocxx::instance inst{};
    const auto uri = mongocxx::uri{"mongodb+srv://<db_username>:<db_password>@orderdatabase.dlypa.mongodb.net/?retryWrites=true&w=majority&appName=OrderDatabase"};
    // Set the version of the Stable API on the client
    mongocxx::options::client client_options;
    const auto api = mongocxx::options::server_api{mongocxx::options::server_api::version::k_version_1};
    client_options.server_api_opts(api);
    // Setup the connection and get a handle on the "admin" database.
    mongocxx::client conn{ uri, client_options };
    mongocxx::database db = conn["admin"];
    // Ping the database.
    const auto ping_cmd = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1));
    db.run_command(ping_cmd.view());
    std::cout << "Pinged your deployment. You successfully connected to MongoDB!" << std::endl;
  }
  catch (const std::exception& e)
  {
    // Handle errors
    std::cout<< "Exception: " << e.what() << std::endl;
  }
  return 0;
}

*/

#include "llama.h"
#include <iostream>
#include <string>

class LlamaModel {
private:
    llama_context* ctx;
    llama_model* model;

public:
    LlamaModel(const std::string& model_path) {
        // Initialisation des paramètres
        llama_context_params params = llama_context_default_params();
        params.n_ctx = 2048;  // Taille du contexte
        params.n_threads = 4;  // Nombre de threads pour l'inférence

        // Chargement du modèle
        model = llama_load_model_from_file(model_path.c_str(), params);
        if (!model) {
            throw std::runtime_error("Échec du chargement du modèle");
        }

        // Création du contexte
        ctx = llama_new_context_with_model(model, params);
        if (!ctx) {
            llama_free_model(model);
            throw std::runtime_error("Échec de la création du contexte");
        }
    }

    std::string generate(const std::string& prompt, int max_tokens = 128) {
        std::string result = prompt;

        // Conversion du prompt en tokens
        std::vector<llama_token> tokens;
        tokens.resize(prompt.size() + max_tokens);
        int n_prompt_tokens = llama_tokenize(ctx, prompt.c_str(), prompt.size(),
            tokens.data(), tokens.size(), true);

        // Génération de tokens
        for (int i = 0; i < max_tokens; i++) {
            // Évaluation du modèle
            if (llama_eval(ctx, tokens.data(), n_prompt_tokens + i, i, params.n_threads)) {
                break;
            }

            // Récupération du token suivant
            llama_token new_token = llama_sample_top_p_top_k(ctx,
                tokens.data(), n_prompt_tokens + i,
                40.0f,  // top_k
                0.95f,  // top_p
                0.8f    // temp
            );

            // Conversion du token en texte
            char buffer[8];
            int len = llama_token_to_str(ctx, new_token, buffer);
            if (len < 0) break;

            result.append(buffer, len);
            tokens[n_prompt_tokens + i] = new_token;
        }

        return result;
    }

    ~LlamaModel() {
        if (ctx) llama_free_context(ctx);
        if (model) llama_free_model(model);
    }
};

int main() {
    try {
        // Chemin vers votre modèle GGUF
        std::string model_path = "chemin/vers/votre/modele.gguf";

        // Création d'une instance du modèle
        LlamaModel llm(model_path);

        // Test de génération
        std::string prompt = "Bonjour, comment allez-vous?";
        std::string response = llm.generate(prompt);

        std::cout << "Prompt: " << prompt << std::endl;
        std::cout << "Réponse: " << response << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}