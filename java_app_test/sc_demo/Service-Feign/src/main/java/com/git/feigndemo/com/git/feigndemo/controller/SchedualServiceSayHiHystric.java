package com.git.feigndemo.com.git.feigndemo.controller;

import com.git.feigndemo.IShedualService;
import org.springframework.stereotype.Component;

@Component
public class SchedualServiceSayHiHystric implements IShedualService {
    @Override
    public String SayHiFromClientOne(String name) {
        return "Feign: sorry" + name;
    }
}
