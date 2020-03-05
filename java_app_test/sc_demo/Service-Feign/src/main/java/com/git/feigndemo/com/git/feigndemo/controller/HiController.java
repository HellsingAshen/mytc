package com.git.feigndemo.com.git.feigndemo.controller;

import com.git.feigndemo.IShedualService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HiController {
    @Autowired
    IShedualService iShedualService;

    @RequestMapping(value="/hi", method = RequestMethod.GET)
    public String sayHi(@RequestParam String name){
        return iShedualService.SayHiFromClientOne(name);
    }
}
