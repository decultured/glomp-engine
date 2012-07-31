game_wrapper = { 
        this_bool = false, 
        that_bool = true, 
        some_value = 7 
}; 

-- allow game_wrapper to inherit from game 
function game_wrapper:__index(key) 
 	local field = rawget(getmetatable(self), key); 
        local retval = nil; 
        
        if type(field) == "nil" then 
                -- key doesn't exist in self, look for it in the prototype object 
                local proto = rawget(self, "game"); 
                field = proto and proto[key]; 
                                
                if type(field) == "function" then 
                        -- key exists as a function on the prototype object 
                        retval = function(obj, ...) 
                                return field(proto, ...); 
                        end; 
                else 
                        -- return whatever this key refers to on the prototype object 
                        retval = field; 
                end; 
        else 
                -- key exists in self 
                if type(field) == "function" then 
                        -- key exists as a function on the self object 
                        retval = function(obj, ...) 
                                return field(self, ...); 
                        end; 
                else 
                        -- return whatever this key refers to on the self object 
                        retval = field; 
                end; 
        end; 
        
        return retval; 
end; 


function game_wrapper:some_function() 
        return self.some_value; 
end; 


function game_wrapper:quit() 
        self:out("A call to game:quit() would usually end the game, but it 
won't now that it's overridden!"); 
end; 


function game_wrapper:new(new_game) 
        gw = { 
                game = new_game 
        }; 
        
        setmetatable(gw, game_wrapper); 

        return gw; 
end; 



my_game = game_wrapper:new(game); 

my_game:out("This prints as if I'd used game:out!"); 
my_game:out("my_game.that_bool is " .. tostring(my_game.that_bool)); 
my_game:out("my_game:some_function() returns " .. 
tostring(my_game:some_function())); 
my_game:quit(); 


--[[ Output would be.. 

This prints as if I'd used game:out! 
my_game.that_bool is true 
my_game:some_function() returns 7 
A call to game:quit() would usually end the game, but it won't now 
that it's overridden! 

]] 
