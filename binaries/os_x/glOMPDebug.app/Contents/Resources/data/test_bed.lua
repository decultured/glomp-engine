new_gfk = graphic.new()

new_gfk:scale(10, 10);

my_table = {
	__self__ = new_gfk
}

base = {
	weird = function (self, whatever)
		return whatever
	end
}


function base:__index(key) 
 	local field = rawget(getmetatable(self), key); 
        local retval = nil; 
        
        if type(field) == "nil" then 
                -- key doesn't exist in self, look for it in the prototype object 
                local proto = rawget(self, "__self__"); 
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

function base:new() 
        new_obj = { 
                __self__ = graphic.new() 
        }; 
        
        setmetatable(new_obj, base); 

        return new_obj; 
end; 


setmetatable( my_table, base)

print (my_table:scale(), my_table:weird("my_table"))

gack = my_table:new()
print (gack:scale(), gack:weird("gack"))

my_table = nil
gack = nil
new_gfk = nil
print ()
collectgarbage()
