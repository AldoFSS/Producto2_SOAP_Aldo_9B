package com.aldo;

import jakarta.jws.WebMethod;
import jakarta.jws.WebService;

@WebService(targetNamespace = "http://www.dataaccess.com/webservicesserver/")
public interface NumberConversion {

    @WebMethod
    public String NumberToWords(long ubiNum);

}