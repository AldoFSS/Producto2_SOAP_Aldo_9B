package com.aldo;

import static spark.Spark.*;

import com.ibm.icu.text.RuleBasedNumberFormat;
import java.util.Locale;

public class App {

    public static void main(String[] args){

        port(8003);

        get("/",(req,res)->{

            String numero=
            req.queryParams("n");

            long n=
            Long.parseLong(numero);

            RuleBasedNumberFormat formato=
            new RuleBasedNumberFormat(
            new Locale("es","ES"),
            RuleBasedNumberFormat.SPELLOUT
            );

            String resultado=
            formato.format(n);

            return resultado;

        });

        System.out.println(
        "Servidor Convertidor activo puerto 8003"
        );

    }
}