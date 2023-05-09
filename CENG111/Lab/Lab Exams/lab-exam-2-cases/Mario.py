def num_safe_paths_to_castle(scouted):
    """
    Returns the number of different ways Mario can reach the castle safely. The
    answer should be zero if the castle cannot be reached safely.

    scouted:   A list of strings. Represents the tiles leading to and around the
               castle. The first element is always "start".
    """
    
    if "castle" not in scouted:
        return 0
    # description does not say there must be a castle so if there is no castle we return 0
    castle = scouted.index("castle")
    scouted = scouted[:castle+1]
    # since we cannot go back we can ignore the tiles after castle
    danger = ["turtle shell", "spike", "hole", "bush"]
    
    if scouted[0] == "castle":
        return 1
    if scouted[0] in danger:
        return 0
    if scouted[0] == "mushroom":
        hype = num_safe_paths_to_castle(scouted[3:])
    # normally we have two ways of going forward but if we are on a mushroom tile we get one more
    else:
        hype = 0
    return num_safe_paths_to_castle(scouted[1:]) + num_safe_paths_to_castle(scouted[2:]) + hype
    # if we are not on the danger or castle we walk, jump and if we are on the mushroom tile hype jump
